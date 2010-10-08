# coding: utf-8
import unittest
from os import path

from sha3lib import hash_functions

from katparser import KAT

class TestLongKat(unittest.TestCase):
    def run_katparser(self, hash_function):
        hash_path = path.dirname(path.abspath(hash_functions.__file__))
        function_path = path.join(hash_path, '%s/' % hash_function)
        kat_path = path.join(function_path, 'kat/LongMsgKAT_256.txt')

        return KAT(kat_path).get_known_answers()

    def run_kat_test(self, function_str):
        known_answers = self.run_katparser(function_str)
        hash_function = '%s256hash' % function_str
        counter = 0
        for kat in known_answers:
            counter += 1
            to_test = "hash_functions.%s(256, %r, %s)" % \
                (hash_function, kat[1], kat[0])
            output_digest = eval(to_test).upper()
            self.assertEquals(output_digest, kat[2],
                'Mismatch:\n%s\n%s' % (to_test, kat[2]))

        print '%s: Tested %i KATs' % (function_str, counter)

    def test_if_the_kats_match(self):
        print "\n"
        for hash_function in hash_functions.HASHES:
            self.run_kat_test(hash_function)

if __name__ == '__main__':
    unittest.main()
