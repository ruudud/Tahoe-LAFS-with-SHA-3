from sha3lib import bmw256 as SHA256
...
class _SHA256d_Hasher:
    ...
    def __init__(self, truncate_to=None):
        self.h = SHA256()
        self.truncate_to = truncate_to
        self._digest = None

    def update(self, data):
        assert isinstance(data, str) # no unicode
        self.h.update(data)

    def digest(self):
        if self._digest is None:
            h1 = self.h.digest()
            del self.h
            if self.truncate_to:
                h1 = h1[:self.truncate_to]
            self._digest = h1

        return self._digest
