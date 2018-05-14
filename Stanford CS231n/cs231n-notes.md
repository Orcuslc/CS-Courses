## Lec 16, Adversarial Examples

1. Adversarial happens because the model is linear.

   - CNNs (and other linear models) can be fooled easily by gradient ascent, and when we add the difference to a clean image, it will be recognized as the wrong character. Example: in ImageNet, if we add the weight (of a linear model) of daisy class to any other classes, all other pics will be classified as daisy. (transferability)
   - They are more likely to be the result of underfitting (e.g. linear seperation)
   - Modern DNNs are very piecewise linear in the relationship between input and output of the model (not the parameters and output since they are multiplied in different layers --> which makes it difficult to train).
   - Fast Gradient Sign Method: 

   $$
    \text{Maximize}~ J(\hat{x}, \theta) = J(x, \theta) + (\hat{x} - x)\top \nabla_x J(x) \\

   \text{subject to}~ \lVert \hat{x}-x\rVert_\infty \le \epsilon \\

   \Rightarrow \hat{x} = x + \epsilon \text{sign}(\nabla_x J(x))
   $$

   - The decision boundaries between true samples and adversarial examples are linear (in both 1d and 2d cases), which means adversarial examples live in linear subspaces (e.g., in MNIST, 25 dim subspace), and by FGSM we can find it through a large dot product with the sign of gradient.
   - Quadratic models do better: e.g. shallow RBF network --> just a template matcher. As it gets deeper, the gradient becomes near 0, which makes it difficult to train.


2. Training on adversarial examples
   - If we train on adversarial examples, we can resist the same type of attack (because training on just original set will case overfitting); but if there is already underfitting, it will make models worse. (regularization)
   - For other models:
     - Linear models: since they cannot learn step functions, it is less useful
     - k-NN: prone to overfitting
   - Virtual adversarial training: unlabeled. after adversarial perturbation, the new guess should match the old guess. (semi-supervised)
   - Model-based optimization: use gradient ascent to maximize some model properties, BUT, in practice, instead of the model telling us how to improve the input, we often get a input (which is not from the training set distribution) that can fools the model into thinking that the input corresponds to something great. (which is adversarial examples)
3. Q&A:
   1. the last layer is very important since it is linear

## Lec 15, Efficient algorithm and hardware for DL 

1. Challenge: model size, speed, energy
2. Algorithms for efficient inference:
   1. pruning and retraining: cut to 10% size and remain the same accuracy
   2. weight sharing: approx. to some discrete numbers and use integers as hashtables
   3. quantization (for weights and activation)
   4. low rank approx for conv and FC
   5. binary/ternary net: (similar w. weight sharing), but transfer to $0, \pm 1$, and remain the same accuracy
   6. winograd conv
3. Algorithms for efficient training:
   1. parallelism
   2. mixed precision, by using fp16 in computation and fp32 in storage
   3. model distillation
   4. dense->sparse->dense training

