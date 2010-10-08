#coding: utf-8
import unittest
from sha3lib import hash_functions
from sha3lib import *
from os import path
import time

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
        self.init_functions()
        k = self.workload
        for function in self.workload:
            t1 = time.time()
            props = self.parse_kat_file(k[function]['file'])
            s = k[function]['function']() 
            for l in xrange(int(props['Repeat'])):
                s.update(props['Text'])
            
            output = s.hexdigest()
            t2 = time.time()
            self.assertEquals(output, props['MD'].lower(),
                    'Mismatch:\n%s\n%s\n%s ' %
                    (function,output,props['MD'].lower()))

            print '%s: Tested ExtremelyLong ok took %0.3f ms' % (function,
                    (t2-t1)*1000.0)
            


if __name__ == '__main__':
    unittest.main()
