CS440-Digit-Classification
==========================
Naïve Bayes Classifier is a widely used classification scheme, which is based on Bayes’ Theorem.
In this part, we were given a data set of 5000 training examples and 1000 test examples of handwriting images and the corresponding labels (digit 0-9).

Data-preprocessing
=========================
Convert each ‘pixel’ like image into a vector of features. In the training sample file, there are 5000 pixel images of handwriting digit of size 20*28. We convert each ‘pixel\’ of ‘#’ or ‘+’ to numerical value 1 and space ‘ ’ to numerical value 0 and thus build a vector of dimension 560 (=20*28) with binary values for each example. Each element in the vector is termed as ‘feature’ of data sample. A sample converted sample is as follows:

Training a Naive Bayesian Classifier
=========================
From the 5000 training samples, we applied Naive Bayesian Classification method as described above. Specifically, we calculate the prior and likelihood probability for each class and features. The prior is a vector that each element corresponds to the percentage of samples of a specific class in the whole training samples. The likelihood is stored in a probability table that for each class (row) Ci and feature (column) Xk represents the likelihood P(Xk|Ci), which is obtained by the total number of  Xk == 1 in sample of class Ci divided by the total number of sample of Ci.
After Calculate the likelihood probability table, Laplacian correction scheme is applied to as a smoothing method to avoid zero probability.

Testing
=========================
With the 100 test examples, total number of correctly classified examples: 766 , with correct ratio: 0.766

Team & Copyright
=============
COPYRIGHT CS440 Group @ University of Illinois at Urbana-Champaign
By Haoran Yu, Le Wang and Tao Feng
