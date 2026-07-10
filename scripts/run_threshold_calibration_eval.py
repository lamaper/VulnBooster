from __future__ import annotations

import argparse
import json
from pathlib import Path

from vulnbooster.calibration import compute_binary_metrics, predict_classifier_probabilities, select_best_threshold
from vulnbooster.config import load_experiment_config
from vulnbooster.env import load_local_env


def main() -> None:
    parser = argparse.ArgumentParser(description="Calibrate classifier thresholds for MCC/Precision on validation data.")
    parser.add_argument("--config", default="configs/full.toml")
    parser.add_argument("--model-dir", required=True)
    parser.add_argument("--valid-path", required=True)
    parser.add_argument("--test-path", required=True)
    parser.add_argument("--target-key", default="func")
    parser.add_argument("--threshold-min", type=float, default=0.3)
    parser.add_argument("--threshold-max", type=float, default=0.8)
    parser.add_argument("--num-thresholds", type=int, default=51)
    args = parser.parse_args()

    load_local_env()
    config = load_experiment_config(args.config)
    model_dir = Path(args.model_dir).resolve()
    valid_path = Path(args.valid_path).resolve()
    test_path = Path(args.test_path).resolve()

    valid_labels, valid_probs = predict_classifier_probabilities(config, model_dir, valid_path, target_key=args.target_key)
    test_labels, test_probs = predict_classifier_probabilities(config, model_dir, test_path, target_key=args.target_key)

    default_test = compute_binary_metrics(test_labels, test_probs, config.training.prediction_threshold)
    best_mcc_valid = select_best_threshold(
        valid_labels,
        valid_probs,
        objective="mcc",
        threshold_min=args.threshold_min,
        threshold_max=args.threshold_max,
        num_thresholds=args.num_thresholds,
    )
    best_precision_valid = select_best_threshold(
        valid_labels,
        valid_probs,
        objective="precision",
        threshold_min=args.threshold_min,
        threshold_max=args.threshold_max,
        num_thresholds=args.num_thresholds,
    )

    payload = {
        "config_path": str(Path(args.config).resolve()),
        "model_dir": str(model_dir),
        "valid_path": str(valid_path),
        "test_path": str(test_path),
        "default_test_metrics": default_test,
        "best_mcc_valid": best_mcc_valid,
        "test_at_best_mcc_valid": compute_binary_metrics(test_labels, test_probs, best_mcc_valid["threshold"]),
        "best_precision_valid": best_precision_valid,
        "test_at_best_precision_valid": compute_binary_metrics(test_labels, test_probs, best_precision_valid["threshold"]),
    }
    print(json.dumps(payload, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
