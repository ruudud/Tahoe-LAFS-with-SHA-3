#coding: utf-8
import unittest

from sha3lib import hash_functions
from sha3lib import *

class BasicHashTester(unittest.TestCase):
    
    def test_init_does_not_segfault(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('foobar')
        # Really just a test to see if the hash functions segfaults,
        # Doesn't assert anything

    def test_update_does_not_segfault(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('foo')
            s.update('barofsoap')
        # Just checks for segfaults

    def test_digest_does_not_segfault(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('foo')
            s.update('barofsoap')
            s.digest()
        # Just checks for segfaults

    def test_update_and_initial_yields_same_result(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('foobar')
            t = f()
            t.update('foo')
            t.update('bar')
            self.assertEquals(s.hexdigest(),t.hexdigest(),
                    'Mismatch:\n%s\n%s\n%s ' %
                    (r, s.hexdigest(), t.hexdigest()))
            #print '%s: Tested OK' % r
    
    def test_possible_to_update_after_final(self):
        #print ""
        for r in hash_functions.HASHES:
            # groestl currently segfaults
            # simd has mismatch, same for JH
            if r in ('groestl','simd'):
                continue
            f = eval(r+'256')
            control = f('foobar').hexdigest()
            s = f('foo')
            s.hexdigest()
            s.update('bar')
            ss = s.hexdigest()
            self.assertEquals(control, ss,
                    'Mismatch:\n%s\n%s\n%s' %
                    (r, control, ss))
            #print '%s: Tested OK' % r


    def test_that_empty_string_and_null_is_not_the_same(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            s = f('')
            t = f(chr(0))
            self.assertNotEquals(s.hexdigest(),t.hexdigest(),
                    'Shouldn\'t match:\n%s\n%s\n%s ' %
                    (r, s.hexdigest(), t.hexdigest()))
            #print '%s: Tested ok' % r
    
    def test_hashfunctions_does_not_end_on_nullbyte(self):
        #print ""
        for r in hash_functions.HASHES:
            f = eval(r+'256')
            text1 = chr(1) + chr(0) + chr(1)
            text2 = chr(1) + chr(0)
            s = f(text1).hexdigest()
            t = f(text2).hexdigest()
            self.assertNotEquals(s,t,
                    'Shouldn\'t match: \n%s\n%s\n%s' %
                    (r, s, t))
            #print '%s: Tested ok' % r

if __name__ == '__main__':
    unittest.main()
