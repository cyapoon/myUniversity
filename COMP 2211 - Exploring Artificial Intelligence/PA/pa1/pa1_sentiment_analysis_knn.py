import numpy as np
import pandas as pd
import scipy.sparse as sparse
from scipy import stats






class KNNModel:
  def __init__(self, k, p):
    self.k = k
    self.p = p

  def fit(self, train_dataset, train_labels):
    self.train_dataset = train_dataset # shape: (num_train_samples, dimension)
    self.train_labels = train_labels # shape: (num_train_samples, )

  def compute_Minkowski_distance(self, test_dataset):
    # TODO
    # dist = np.expand_dims(self.train_dataset,axis=0)-np.expand_dims(test_dataset,axis=1)
    # dist = np.abs(dist)
    # dist = np.power(dist,self.p)
    # dist = np.sum(dist,axis=2)
    # dist = np.power(dist,1/self.p)
    dist = np.empty((test_dataset.shape[0],self.train_dataset.shape[0]))
    #print(dist.shape)
    for i in range(test_dataset.shape[0]):
      temp = np.power(np.sum(np.abs(self.train_dataset - test_dataset[i])**self.p,axis=1),(1/self.p))
      #print(temp.shape)
      dist[i] = temp
    #print(dist.shape)
    return dist # shape: (num_test_samples, num_train_samples)

  def find_k_nearest_neighbor_labels(self, test_dataset):
    # TODO
    dist = self.compute_Minkowski_distance(test_dataset)
    sort_ind = np.argsort(dist,axis=1)
    #print(sort_ind)
    
    k_nearest_neighbor_labels = np.take(self.train_labels,sort_ind[:,0:self.k])
    #print(k_nearest_neighbor_labels.shape)
    return k_nearest_neighbor_labels # shape: (num_test_samples, self.k)
    
  def predict(self, test_dataset):
    # TODO
    labels = self.find_k_nearest_neighbor_labels(test_dataset)
    labels = labels.astype(int)
    count = np.empty(0)
    
    #print(labels.shape)
    count = count.astype(int)
    #print(count.dtype)
    for i in range(labels.shape[0]):
      count = np.append(count,np.bincount(labels[i],minlength=np.amax(labels)+1),axis=0)
      
    #print(count.dtype)
    
    test_predict = np.argmax(count.reshape(-1,np.amax(labels)+1),axis=1)
    #print(test_predict.shape)
    
    return test_predict # shape: (num_test_samples, )



def generate_confusion_matrix(test_predict, test_labels):
  # TODO
  num_classes = np.amax(test_labels) + 1
  
  confusion_matrix = np.empty((num_classes,num_classes))
  #print(confusion_matrix.shape)
  for i in range(num_classes):
    for j in range(num_classes):
      actual = (test_labels==i).astype(int)
      predict = (test_predict==j).astype(int)
      #print(actual.dtype,predict.dtype)
      # print(confusion_matrix.shape)
      confusion_matrix[i][j] =np.dot(actual,predict)
  # index = np.arange(num_classes)
  # index = np.tile(index,(test_labels.shape[0],1))
  # index = np.transpose(index)
  
  # actual = np.equal(test_labels,index)
  # #print(actual.shape)
  # actual = np.expand_dims(actual,1)

  # predict = np.equal(test_predict,index)
  # #print(predict.shape)
  # predict = np.expand_dims(predict,0)
  # #print(actual.shape,predict.shape)

  # confusion_matrix = actual*predict
  # confusion_matrix = np.sum(confusion_matrix,axis=2).astype(float)
  # #print(confusion_matrix.shape)    
  return confusion_matrix # shape: (num_classes, num_classes)
  

def calculate_accuracy(test_predict, test_labels):
  # TODO
  tp = generate_confusion_matrix(test_predict,test_labels)
  sum_diag = np.sum(np.diagonal(tp))
  num_sample = test_labels.shape[0]
  accuracy = sum_diag/num_sample
  return accuracy # dtype: float
  
def calculate_precision(test_predict, test_labels):
  # TODO
  cm = generate_confusion_matrix(test_predict,test_labels)
  dia = np.diagonal(cm)
  tp_fp = np.sum(cm, axis=0)
  precision = np.average(dia/tp_fp)
  return precision # dtype: float


def calculate_recall(test_predict, test_labels):
  # TODO
  cm = generate_confusion_matrix(test_predict,test_labels)
  dia = np.diagonal(cm)
  tp_fn = np.sum(cm,axis=1)
  recall = np.average(dia/tp_fn)
  return recall # dtype: float


def calculate_macro_f1(test_predict, test_labels):
  # TODO
  mac = calculate_precision(test_predict,test_labels)
  mar = calculate_recall(test_predict,test_labels)
  macro_f1 = 2 * (mac*mar)/(mac+mar)
  return macro_f1 # dtype: float


def calculate_MCC_score(test_predict, test_labels):
  # TODO
  cm = generate_confusion_matrix(test_predict, test_labels)
  #print(cm.shape)
  tp = np.diagonal(cm)
  num_samples = test_labels.shape[0]
  tp_fp = np.sum(cm,axis=0)
  tp_fn = np.sum(cm,axis=1)
  num_samples_square = np.power(num_samples,2)
  tp_fp_square = np.power(tp_fp,2)
  tp_fn_square = np.power(tp_fn,2)
  sum_tp = np.sum(tp)
  #print(tp_fp.shape,tp_fn.shape)
  sum_tp_fp_fn = np.dot(tp_fp,tp_fn)
  sum_tp_fp_square = sum(tp_fp_square)
  sum_tp_fn_square = sum(tp_fn_square)
  denominator = np.sqrt((num_samples_square-sum_tp_fp_square)*(num_samples_square-sum_tp_fn_square))
  #if denominator == 0:
  #  return 0
  MCC_score = (sum_tp*num_samples-sum_tp_fp_fn)/denominator
  return MCC_score # dtype: float


class DFoldCV:
  def __init__(self, X, y, k_list, p_list, d, eval_metric):
    self.X = X
    self.y = y
    self.k_list = k_list
    self.p_list = p_list
    self.d = d
    self.eval_metric = eval_metric

  def generate_folds(self):
    # TODO
    reshape_y = self.y.reshape(-1,1)
    #print(reshape_y.shape)
    aug_matrix = np.concatenate((self.X,reshape_y),axis=1)
    temp_list = np.array_split(aug_matrix,self.d)
    temp_array = np.array(temp_list)
    #print(temp_array.shape)
    #train_d_folds = np.empty((self.d,int(temp_array.shape[1]*(self.d-1)),temp_array.shape[2]))
    #test_d_folds = np.empty((d,int(temp_array.shape[1]),temp_array.shape[2]))
    train_d_folds = []
    test_d_folds = []
    #print(train_d_folds.shape)
    #print(test_d_folds.shape)
    for i in range(self.d):
      index = np.arange(self.d)
      #print(temp_array[index!=i].shape)
      #train_d_folds[i] = temp_array[index!=i].reshape(-1,temp_array.shape[2])
      #test_d_folds[i] = temp_array[i]
      train_d_folds.append(temp_array[index!=i].reshape(-1,temp_array.shape[2]))
      test_d_folds.append(temp_array[i])
      
    #print(np.array(train_d_folds).shape)
    #print(np.array(test_d_folds).shape)
    return train_d_folds, test_d_folds # type: tuple
  
  def cross_validate(self):
    # TODO
    scores = np.empty((len(self.k_list),len(self.p_list),self.d))
    train,test = self.generate_folds()
    train = np.array(train)
    test = np.array(test)
    #print(train[:5,:5,:5])
    #print(test[:5,:5,:5])
    #print(train.shape)
    #print(test.shape)
    for i in range(len(self.k_list)):
      for j in range(len(self.p_list)):
        for k in range(self.d):
          train_data = train[k,:,:-1]
          train_label = train[k,:,-1]
          pred_data = test[k,:,:-1]
          pred_label = test[k,:,-1]
          train_label = train_label.astype(int)
          pred_label = pred_label.astype(int)
          knn_model = KNNModel(self.k_list[i],self.p_list[j])
          #print(train[i,:,:-1].shape)
          #print(train[i,:,-1].astype(int).shape)
          knn_model.fit(train_data,(train_label))
          #print(test[i,:,:-1].shape)
          pred = knn_model.predict(pred_data)
          #print(pred.shape)
          #print(test[i,:,-1].shape)
          scores[i,j,k] = self.eval_metric(pred,(pred_label))
    return scores # shape: (length of self.k_list, length of self.p_list, self.d)


  def validate_best_parameters(self):
    # TODO
    scores = self.cross_validate()
    average_scores = np.average(scores,axis=2)
    #print(average_scores.shape)
    best_index = np.argmax(average_scores)
    k_index, p_index = np.unravel_index(best_index,(scores.shape[0],scores.shape[1]))
    k_best = self.k_list[k_index]
    p_best = self.p_list[p_index]
    return k_best, p_best # type: tuple

