import sys
import pickle
import numpy as np
import keras

s=sys.argv[2]
model=keras.models.load_model(s)
test = pickle.load(open(sys.argv[1]+'test.p','rb'))

test_data=np.array(test['data']).reshape(10000,3,32,32)
test_data=test_data.astype('float32')/255.


result=model.predict(test_data)

answer=np.zeros((10000))

for i in range(10000):
	tmp=result[i]
	answer[i]=tmp.argmax()

f=open(sys.argv[3],'w');
f.write('ID,class\n')
for i in range(10000):
	f.write('%d'%(test['ID'][i]))
	f.write(',')
	f.write('%d'%(answer[i]))
	f.write('\n')



