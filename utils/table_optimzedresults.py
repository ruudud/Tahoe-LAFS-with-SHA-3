#!/usr/bin/python
#coding: utf-8
from os.path import join as pjoin
from os import getlogin

RESULTS_DIR='/home/'+getlogin()+'/Tahoe-LAFS-with-SHA-3/results/tahoe-datalengths/sha256-1'
TEST_VECTORS = ('1b','1kb','1mb','100mb','1gb')
CYCLES = 2833000000
OPS=('p','g')

MEDIANS = {
        'blake': {
                'long':8.38,
                4096:8.58,
                1563:8.92,
                576:9.81,
                64:21.25,
                8:107.38,
            },
        'bmw':{
                'long':6.94,
                4096:7.29,
                1563:7.71,
                576:8.88,
                64:23.78,
                8:132.88,
            },
        'cubehash':{
                'long':13.23,
                4096:14.45,
                1563:16.37,
                576:21.21,
                64:91.50,
                8:633,
            },
        'echo':{
                'long':32.64,
                4096:32.77,
                1563:35.91,
                576:42.87,
                64:101.33,
                8:807.50,
            },
        'fugue':{
                'long':17.64,
                4096:19.28,
                1563:21.98,
                576:29.25,
                64:123.91,
                8:862.75,
            },
        'groestl':{
                'long':23.47,
                4096:24.16,
                1563:25.28,
                576:28.26,
                64:65.08,
                8:339.0,
            },
        'hamsi':{
                'long':29.96,
                4096:30.14,
                1563:30.39,
                576:30.94,
                64:40.38,
                8:117.88,
            },

        'jh':{
                'long':18.96,
                4096:19.32,
                1563:19.90,
                576:21.49,
                64:40.38,
                8:329.38,
            },
        'keccak':{
                'long':20.88,
                4096:21.49,
                1563:22.31,
                576:25.12,
                64:50.34,
                8:401.62,
            },
        'luffa':{
                'long':13.53,
                4096:13.87,
                1563:14.43,
                576:15.86,
                64:33.59,
                8:145.62,
            },
        'skein':{
                'long':18.61,
                4096:18.63,
                1563:18.96,
                576:19.95,
                64:32.53,
                8:184.88,
            },
        'shabal':{
                'long':6.01,
                4096:6.44,
                1563:7.18,
                576:9.16,
                64:35.06,
                8:229.50,
            },
        'shavite3':{
                'long':32.25,
                4096:32.89,
                1563:33.93,
                576:36.76,
                64:73.05,
                8:329.38,
            },
        'simd':{
                'long':11.15,
                4096:11.52,
                1563:11.87,
                576:12.97,
                64:25.56,
                8:218.88,
            },
        'sha256':{
                'long':15.14,
                4096:15.83,
                1563:16.45,
                576:18.05,
                64:38.12,
                8:179.62,
                }
        
        }

def read_data(group,oper):
    assert (oper in ('p','g'))
    assert(group in TEST_VECTORS)
    result_file = group + "_data" + oper + ".txt"
    fname = pjoin(RESULTS_DIR,result_file)
    handle = open(fname,'r')
    turn = []
    for i in handle.readlines():
        turn.append(int(i))

    return turn


def interpol(x1,y1,x2,y2):
    # Assuming x2>x1
    # Assuming y1<y2
    k = 0.0
    r = 0.0
    k += x2-x1
    r += y2-y1
    return float(r/k)

def estimate_time(dl_list,saveas):
    for key in MEDIANS:
        s = 0
        for inp in dl_list:
            s += inp*correct_time(key,inp)
        time = s/(CYCLES)
        k = "%.4f" % time
        MEDIANS[key][saveas] = k
        
def correct_time(key,value):
    if value in (4096,1563,576,64,8):
        return MEDIANS[key][value]
    elif value>4096:
        return MEDIANS[key]['long']
    elif value>1563:
        return MEDIANS[key][1563] + (value-1563)*interpol(4096,MEDIANS[key][4096],1536,MEDIANS[key][1563])
    elif value>576:
        return MEDIANS[key][576] + (value-576)*interpol(1563,MEDIANS[key][1563],576,MEDIANS[key][576])
    elif value>64:
        return MEDIANS[key][64] + (value-64)*interpol(576,MEDIANS[key][576],64,MEDIANS[key][64])
    elif value>8:
        return MEDIANS[key][8] + (value-8)*interpol(64,MEDIANS[key][64],8,MEDIANS[key][8])
    else:
        print error

def write_latex_table(op):
    if op=='p':
        word = "upload"
    else:
        word = "download"
    caption = "Time spent hashing during "+word+" using best SHA-3 candidate implementations"

    all_data = "\\begin{table} \n"
    all_data +="  \\centering \n"
    all_data +="    \\begin{tabular}{ | l | r | r | r | r | r | }\n"
    all_data +="      \\hline\n" 
    headers = ['Candidate','1B','1KB','1MB','100MB','1GB']
    func =['BLAKE','BMW','Echo','Fugue','Groestl','Hamsi',
           'JH','Keccak','Luffa','SHA256','Simd','Skein','Shabal','Shavite3']
    func.sort(reverse=True)
    header = "      "
    body = ""
    for h in headers:
        header += "\\textbf{"+h+"} & "
    header = header[:-2] + "\\\\ \\hline\n"
    
    for f in func:
        if func=='Groestl':
            k = "      Grøstl & "
        k = "      "+str(f) + " & "
        for tv in TEST_VECTORS:
            k += str(MEDIANS[f.lower()][str(tv)+str(op)]) + " & "
        k = k[:-2] + "\\\\ \hline\n"
        body += k
    all_data += header
    all_data += body
    all_data +=  "      \\end{tabular} \n"
    all_data +=  "      \\caption{"+caption+"}\n"
    all_data +=  "      \\label{tbl:tahoe:optimized_"+op+"}\n"
    all_data +=  "\\end{table}\n"
    
    folder = '/home/'+getlogin()+'/Tahoe-LAFS-with-SHA-3/paper/tables'
    filename = folder +'/tahoe_optimized_'+str(op)+'.tex'
    handle = open(filename,'w')
    handle.write(all_data)
    handle.close()



for op in OPS:
    for tv in TEST_VECTORS:
        data = read_data(tv,op)
        estimate_time(data,tv+op)

if __name__ == '__main__':
    write_latex_table('p')
    write_latex_table('g')
    print "Wrote two tables"
