import shutil
import os
import pickle, gzip

import mytoken as tk
import build_dataset as bd
from pattern import StmtInsPos, DeclInsPos
from tqdm import tqdm


def dataset(save_dir, dir='./tmp', tgt='data.pkl.gz',
            symtab='oj_uid.pkl.gz',
            inspos_file='oj_inspos.pkl.gz',
            done_file='dataset.done'):
            
    # 检查是否存在数据文件
    file_num = 0
    for root, dirs, files in os.walk(os.path.join(dir, domain)):
        file_num += len(files)
        
    if file_num == 0:
        print(f"❌ 未在 {os.path.join(dir, domain)} 中找到 .c 文件，请先运行准备脚本！")
        return
        
    print(f"✅ 找到 {file_num} 个 .c 文件，开始进行预处理...")
    
    d = tk.tokenize(dir=dir, src=domain, save_dir=save_dir)
    if d is not None:
        train, test = bd.split(d)
        
        idx2txt, txt2idx = bd.build_vocab(train['raw'])
        print('vocab size:', len(idx2txt))
        
        train_tokens = bd.text2index(train['raw'], txt2idx)
        test_tokens = bd.text2index(test['raw'], txt2idx)
        
        uids =[]
        for _uids in train["uids"]:
            if _uids is not None: # 增加安全校验
                for _uid in _uids.keys():
                    if _uid not in uids:
                        uids.append(_uid)
                        
        if not os.path.isfile(os.path.join(save_dir, done_file)):
            data = {"raw_tr": train["raw"], "y_tr": train["labels"],
                    "x_tr": train_tokens,
                    "raw_te": test["raw"], "y_te": test["labels"],
                    "x_te": test_tokens,
                    "idx2txt": idx2txt, "txt2idx": txt2idx}
                    
            uid = {"tr": train["uids"], "te": test["uids"], "all": uids}
            
            print("💾 正在保存基础数据与字典...")
            with gzip.open(os.path.join(save_dir, tgt), "wb") as f:
                pickle.dump(data, f)
            with gzip.open(os.path.join(save_dir, symtab), "wb") as f:
                pickle.dump(uid, f)
                
            print("🔍 正在扫描干预锚点 (Stmt & Decl) ... 这可能需要几分钟...")
            stmt_poses_tr =[StmtInsPos(tr) for tr in tqdm(train['raw'], desc="Train Stmt")]
            stmt_poses_te =[StmtInsPos(te) for te in tqdm(test['raw'], desc="Test Stmt")]
            decl_poses_tr =[DeclInsPos(tr) for tr in tqdm(train['raw'], desc="Train Decl")]
            decl_poses_te =[DeclInsPos(te) for te in tqdm(test['raw'], desc="Test Decl")]
            
            inspos = {"stmt_tr": stmt_poses_tr, "stmt_te": stmt_poses_te,
                      "decl_tr": decl_poses_tr, "decl_te": decl_poses_te}
                      
            print("💾 正在保存干预坐标集...")
            with gzip.open(os.path.join(save_dir, inspos_file), "wb") as f:
                pickle.dump(inspos, f)
                
            with open(os.path.join(save_dir, done_file), "wb") as f:
                pass 
            print("🎉 预处理全部完成！")


if __name__ == "__main__":
    # ==========================================
    # 请根据需要在这里切换任务目标： 'reveal' 或 'devign'
    # ==========================================
    TASK_NAME = 'reveal'  
    
    data_root = f'../data_raw/{TASK_NAME}/'
    save_path = f'../data/{TASK_NAME}/dataset/'

    domain = 'origin_s'
    
    tmp = data_root
    tmp_dir = os.path.join(data_root, domain)
    save_dir = os.path.join(save_path, domain)
    
    os.makedirs(save_dir, exist_ok=True)

    if os.path.exists(os.path.join(tmp_dir, 'dataset.done')):
        os.remove(os.path.join(tmp_dir, 'dataset.done'))
        
    dataset(save_dir, dir=tmp)