#coding: utf-8
import unittest

from sha3lib import hash_functions
from sha3lib import *

class HashCopyTester(unittest.TestCase):
    
    def test_hashfunctions_support_copy_of_nonfinished_hash(self):
        #print ""
        for r in hash_functions.HASHES:
            # SIMD does not support this for an odd reason
            if r in ('simd'):
                continue 
            
            f = eval(r+'256')
            s = f('foo')
            u = s.copy()
            self.assertEquals(s.hexdigest(),u.hexdigest(),
                    'Mismatch: \n%s\n%s\n%s' %
                    (r, s.hexdigest(), u.hexdigest()))
            #print '%s: Tested ok' % r

    def test_update_of_copied_does_not_affect_original(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('foo')
            t = s.copy()
            ss = s.hexdigest()
            t.update('bar')
            self.assertEquals(ss, s.hexdigest(),
                    'Mismatch: \n%s\n%s\n%s' %
                    (r, ss, s.hexdigest()))
            #print '%s Tested ok' % r
    
    def test_copied_object_support_update(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            control = f('foobar').hexdigest()
            s = f('foo')
            t = s.copy()
            t.update('bar')
            u = t.hexdigest()
            self.assertEquals(control,u,
                    'Mismatch: \n%s\n%s\n%s' %
                    (r, control, u))
            #print '%s Tested ok' % r

    def test_hashfunctions_support_copy_of_finished_hash(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            orig = f('foobar')
            check = orig.hexdigest()
            copy = orig.copy()
            cc = copy.hexdigest()
            self.assertEquals(check, cc,
                    'Mismatch: \n%s\n%s\n%s' %
                    (r, check, cc))
            #print '%s Tested ok' % r

    def test_support_copy_and_update_of_finished_hash(self):
        #print ""
        for r in hash_functions.HASHES:
            # SIMD does not support this in sha3lib
            if r in ('simd'):
                continue
            f = eval(r+'256')
            control = f('foobar').hexdigest()
            orig = f('foo')
            oo = orig.hexdigest()
            copy = orig.copy()
            copy.update('bar')
            cc = copy.hexdigest()
            self.assertEquals(cc, control,
                    'Mismatch: \n%s\n%s\n%s' %
                    (r, control, cc))
            #print '%s Tested ok' % r

if __name__ == '__main__':
    unittest.main()
