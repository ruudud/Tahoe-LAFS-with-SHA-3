import unittest

from katparser import KAT

from bmw import hash

class TestShortKat(unittest.TestCase):
    def setUp(self):
        self.known_answers = KAT('ShortMsgKAT_256.txt').get_known_answers()

    def test_if_the_kats_match(self):
        counter = 0
        for kat in self.known_answers:
            counter += 1
            to_test = hash(256, kat[1], kat[0])
            self.assertEquals(to_test, kat[2],
                'Mismatch:\n%s\n%s' % (to_test, kat[2]))

        print 'Tested %i KATs' % counter

if __name__ == '__main__':
    unittest.main()
