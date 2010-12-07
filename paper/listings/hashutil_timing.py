import time

class _SHA256d_Hasher:
    def update(self, data):
        t1 = time.time()
        self.h.update(data)
        t2 = time.time()

        self.time_spent_hashing += t2 - t1

    def digest(self):
        if self._digest is None:
            t1 = time.time()
            h1 = self.h.digest()
            t2 = time.time()

            self.time_spent_hashing += t2 - t1

            _write_increase(HASH_TIMING_FILE,
                            self.time_spent_hashing)
