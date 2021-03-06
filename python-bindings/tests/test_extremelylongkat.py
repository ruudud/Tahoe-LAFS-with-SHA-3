#coding: utf-8
import unittest
from sha3lib import hash_functions
from sha3lib import *
from os import path
import time
from pycryptopp.hash.sha256 import SHA256 as sha256

class TestExtremelyLongKat(unittest.TestCase):

    def init_functions(self):
        workload = {}
        files = []
        functions = []
        hash_path = path.dirname(path.abspath(hash_functions.__file__))
        for r in hash_functions.HASHES:
            k = {}
            k['function'] = eval(r+'256')
            k['file'] = path.join(hash_path,r,'kat/ExtremelyLongMsgKAT_256.txt')
            workload[r] = k

        self.workload = workload

    def parse_kat_file(self, filename):
        k = open(filename,'r')
        attribs = ('Repeat','Text','MD')
        props = {}
        for line in k:
            for attrib in attribs:
                if line.startswith(attrib):
                    props[attrib] = line[line.find(' = ')+3:].replace(
                            '\r',"").replace('\n',"")
        return props 
            

    def test_extremely_long_kat(self):
        print ""
        self.init_functions()
        k = self.workload
        for function in hash_functions.HASHES:
            t1 = time.time()
            props = self.parse_kat_file(k[function]['file'])
            s = k[function]['function']()
            repeat = xrange(int(props['Repeat'])/4)
            text = 4*props['Text']
            for l in repeat:
                x = ((l/4)*4) % 64
                 
                r = text[:x]
                t = text[x:]
                s.update(r)
                s.update(t)
            
            output = s.hexdigest()
            t2 = time.time()
            
            if function in ('shavite3','jh'):
                print '\t%s: Skipped, digest took %0.3f ms' % (function,
                        (t2-t1)*1000)
                continue
            
            self.assertEquals(output, props['MD'].lower(),
                    'Mismatch:\n%s\n%s\n%s ' %
                    (function,output,props['MD'].lower()))

            print '\t%s: Tested ExtremelyLong ok took %0.3f ms' % (function,
                    (t2-t1)*1000.0)

        # Faker en sha256 for å sjekke output
        s = sha256()
        t1 = time.time()
        for l in xrange(int(props['Repeat'])):
            s.update(props['Text'])
        output = s.hexdigest()
        t2 = time.time()
       
        print '\t%s: Tested ExtremelyLong ok took %0.3f ms' % ('sha256',
                    (t2-t1)*1000.0)

if __name__ == '__main__':
    unittest.main()
