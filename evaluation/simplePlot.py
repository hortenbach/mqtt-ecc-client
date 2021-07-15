import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 10})
plt.rcParams.update({'font.family': 'small'})
plt.rcParams.update({'legend.loc' : 'upper right'})
import numpy as np
import glob, os

os.chdir("./messungen")

def getData():
  files = glob.glob("*.npy")
  data = {}
  for FILE in files:
    with open(FILE,"rb") as f:
      name = FILE.split('.')[0]
      print("Loading data from file " + name)
      data[name] = np.load(f)
  f.close()
  return data

def cleanDataset(dset):
  print("Dataset original length: " + str(len(dset)))
  last = 0
  start = []
  for idx, val in enumerate(dset):
    if val == 0:
      last = 1
    elif last == 1:
      last = 0
      start.append(idx)      
  dSets = np.split(dset, start)
  dClean = []
  for s in dSets:
    # print(s)
    if s.shape[0] > 11000:
      dClean.append(s[:6000])  
  dClean.pop(0)
  return dClean

def evaluateAVGT(data, name):
  avg = 0
  t = 0
  for d in data:
    avg =avg + np.average(d)
    t = t + len(d)
  t = t/len(data)
  avg = avg/len(data)
  print("AVG curr all \t" + name + "  :\t" + str(avg))
  print("AVG t all \t" + name + "  :\t" + str(t))


def writeEval(data, PATH, plottitle):
  avg = 0
  itxt = open(PATH+"Info_plots_total_average.txt", "a")
  for i in range(int(len(data)/10)):  
    fig, ax = plt.subplots(nrows=1, ncols=1)
    fig.set_size_inches(10,7)
    plt.title(plottitle)
    for j in range(10):
      avgPlot = np.average(data[i*j])
      avg = avg + np.average(data[i*j])
      ax.plot(data[i*j], label="avg "+str(avgPlot))
    ax.legend()
    fig.savefig(PATH + str(i) + '.png')
    plt.close(fig)
    istr = "Plot " + str(i) + " avg: " + str(avg/10)
    # print(istr)
    itxt.write(istr + "\n")
  print("AVG all " + plottitle + "  :" + str(avg/len(data)))
  itxt.close()

def checkDir(fdir):
  if not os.path.exists(fdir):
    os.makedirs(fdir)

##### Process Data
# set folderstructure
folder1 = './plot_ecc_without_ACC/'
folder2 = './plot_ecc_with_ACC/'
folder3 = './plot_rsa_without_ACC/'
folder4 = './plot_rsa_with_ACC/'
folder5 = './plot_mqtt_without_TLS/'

checkDir(folder1)
checkDir(folder2)
checkDir(folder3)
checkDir(folder4)
checkDir(folder5)

dataSets = getData()

ecc = cleanDataset(dataSets['ecc_without_ACC_4124s'])
writeEval(ecc, folder1+'ecc_without_ACC_', 'TLS ECC without HW Acceleration (MPI)')
evaluateAVGT(ecc, 'TLS ECC without HW Acceleration (MPI)')

eccAcc = cleanDataset(dataSets['ecc_with_ACC_4541s'])
writeEval(eccAcc, folder2+'ecc_with_ACC_', 'TLS ECC with HW Acceleration (MPI)')
evaluateAVGT(eccAcc, 'TLS ECC with HW Acceleration (MPI)')

rsa = cleanDataset(dataSets['rsa_without_ACC_3967s'])
writeEval(rsa, folder3+'rsa_without_ACC_', 'TLS RSA without HW Acceleration (MPI)')
evaluateAVGT(rsa, 'TLS RSA without HW Acceleration (MPI)')

rsaAcc = cleanDataset(dataSets['rsa_with_ACC_4125s'])
writeEval(rsaAcc, folder4+'rsa_with_ACC_', 'TLS RSA with HW Acceleration (MPI)')
evaluateAVGT(rsaAcc, 'TLS RSA with HW Acceleration (MPI)')

mqtt = cleanDataset(dataSets['mqtt_without_TLS_3561s'])
writeEval(mqtt, folder5+'mqtt_without_TLS_', 'MQTT without TLS')
evaluateAVGT(mqtt, 'MQTT without TLS')