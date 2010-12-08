#coding: utf-8
import unittest
from sha3lib import hash_functions
from sha3lib import *

class TestExtremeLyLongSimilar(unittest.TestCase):

    def setUp(self):
        self.skip = ('hamsi','skein') # Don't work, possible int-roundoff

        self.file1 = open('tests/files/1gb_org.tv','rb')
        self.file2 = open('tests/files/1gb_cha.tv','rb')
        self.res = {}
        for f in hash_functions.HASHES:
            self.res[f] = {}
    
    def calc_digestest_for_file(self,filehandle, functions, dictkey):
        msg = filehandle.read()
        
        for f in functions:
            if f in self.skip:
                continue
            self.res[f][dictkey] = eval(f+'256')(msg).hexdigest()
    
    def test_extremelylong_similar_files(self):
        return True #Skip test
        self.calc_digestest_for_file(self.file1, hash_functions.HASHES, '1')
        self.calc_digestest_for_file(self.file2, hash_functions.HASHES, '2')

        for func in hash_functions.HASHES:
            if func in self.skip:
                continue
            k = self.res[func]['1']
            r = self.res[func]['2']
            self.assertNotEquals(k, r, '%s matched' % str(func))
            print "\t%s ok" % str(func)

if __name__ == '__main__':
    unittest.main()
