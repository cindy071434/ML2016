import pickle
import sys
import numpy as np
import keras
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation,Reshape
from keras.layers.normalization import BatchNormalization
from keras.layers.advanced_activations import PReLU
from keras.utils import np_utils, generic_utils
from keras.optimizers import SGD
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.optimizers import SGD, Adadelta, Adagrad
from keras import backend as K
K.set_image_dim_ordering('th')


s=sys.argv[1]
all_label = pickle.load(open(s+'all_label.p','rb'))
all_unlabel = pickle.load(open(s+'all_unlabel.p','rb'))

data_unlabel = []
data_label = []
class_label = []
class_unlabel = []

for i in range(10):
	for j in range(500):
		data_label.append(all_label[i][j])
		class_label.append([i])

for i in range(45000):
	data_unlabel.append(all_unlabel[i])
	class_unlabel.append(0)
data_label = np.array(data_label)
data_unlabel = np.array(data_unlabel)
class_label = np.array(class_label)
class_unlabel = np.array(class_unlabel)
data_label = data_label.reshape(5000,3,32,32)
data_label = data_label.astype('float32')/255.
data_unlabel = data_unlabel.reshape(45000,3,32,32)
data_unlabel = data_unlabel.astype('float32')/255.


model = Sequential()
model.add(Convolution2D(16, 3, 3, input_shape=(3,32, 32)))
model.add(Activation('relu'))
model.add(Convolution2D(32, 3, 3))
model.add(Activation('relu'))
model.add(MaxPooling2D((2,2)))
model.add(Dropout(0.4))
model.add(Convolution2D(64, 3, 3))
model.add(Activation('relu'))
model.add(Convolution2D(64, 3, 3))
model.add(Activation('relu'))
model.add(MaxPooling2D((2,2)))
model.add(Dropout(0.4))
model.add(Flatten())
model.add(Dense(output_dim=256))
model.add(Activation('relu'))
model.add(Dropout(0.4))
model.add(Dense(output_dim=10))
model.add(Activation('softmax'))

model.compile(loss = 'sparse_categorical_crossentropy',optimizer = 'adam',metrics = ['accuracy'])
model.fit(data_label, class_label, batch_size = 100, nb_epoch =5)
score=model.evaluate(data_label,class_label)
print('loss = ',score[0])
print('acc = ',score[1])

while score[1]<0.9:
	model.fit(data_label,class_label,batch_size=100,nb_epoch=5)
	score=model.evaluate(data_label,class_label)
	print('loss = ',score[0])
	print('acc = ',score[1])


m=0
while data_unlabel.shape[0]>10000 :
	pre_temp=model.predict(data_unlabel)
	count_unlabel=np.zeros((data_unlabel.shape[0]))
	counter1=0
	counter2=0
	for i in range(data_unlabel.shape[0]):
		if np.max(pre_temp[i])>0.7:
			count_unlabel[i]=np.argmax(pre_temp[i])
			counter1=counter1+1
		else:
			count_unlabel[i]=10
			counter2=counter2+1

	t_data_unlabel=np.zeros((counter2,3,32,32))
	t_class_unlabel=np.zeros((counter2,1))

	t_data_label=np.zeros((counter1,3,32,32))
	t_class_label=np.zeros((counter1,1))
	a=0
	b=0
	for i in range(data_unlabel.shape[0]):
		if count_unlabel[i]==10:
			t_data_unlabel[a]=data_unlabel[i]
			a=a+1
		else:
			t_data_label[b]=data_unlabel[i]
			t_class_label[b]=count_unlabel[i]
			b=b+1

	data_unlabel=t_data_unlabel
	class_unlabel=t_class_unlabel
	data_label=np.vstack((data_label,t_data_label))
	class_label=np.vstack((class_label,t_class_label))

	model = Sequential()
	model.add(Convolution2D(16, 3, 3, input_shape=(3,32, 32)))
	model.add(Activation('relu'))
	model.add(Convolution2D(32, 3, 3))
	model.add(Activation('relu'))
	model.add(MaxPooling2D((2,2)))
	model.add(Dropout(0.4))
	model.add(Convolution2D(64, 3, 3))
	model.add(Activation('relu'))
	model.add(Convolution2D(64, 3, 3))
	model.add(Activation('relu'))
	model.add(MaxPooling2D((2,2)))
	model.add(Dropout(0.4))
	model.add(Flatten())
	model.add(Dense(output_dim=256))
	model.add(Activation('relu'))
	model.add(Dropout(0.4))
	model.add(Dense(output_dim=10))
	model.add(Activation('softmax'))
	model.compile(loss='sparse_categorical_crossentropy',optimizer='Adam',metrics=['accuracy'])
		
	q=0
	model.fit(data_label,class_label,batch_size=100,nb_epoch=5)
	score=model.evaluate(data_label,class_label)
	print('loss = ',score[0])
	print('acc = ',score[1])
	
	while score[1]<0.9:
		q=q+1
		model.fit(data_label,class_label,batch_size=100,nb_epoch=5)
		score=model.evaluate(data_label,class_label)
		print('loss = ',score[0])
		print('acc = ',score[1])
	
	m=m+1


for q in range (2):
	model.fit(data_label,class_label,batch_size=100,nb_epoch=5)
	score=model.evaluate(data_label,class_label)
	print('loss = ',score[0])
	print('acc = ',score[1])

model.save(sys.argv[2])

