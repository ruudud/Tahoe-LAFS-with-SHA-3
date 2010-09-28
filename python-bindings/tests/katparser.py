class KAT():
    def __init__(self, filename=None):
        if not filename:
            raise ValueError('Please give filename')
        self.filename = filename
        self.kats = None
        
    def get_known_answers(self):
        if self.kats:
            return self.kats

        f = open(self.filename, 'r') 
        kats = []
        kat = []
        for line in f:
            attrib = line[:3]
            attribs = ('Len', 'Msg', 'MD ')
            if attrib in attribs:
                value_from = line.find('=') + 2
                value = line[value_from:].replace('\r','')
                value = value.replace('\n','')

                if attrib == 'Len':
                    kat.append(int(value))                    
                elif attrib == 'Msg':
                    # Split the msg into two and two, and chr it up
                    values = [value[i:i+2] for i in xrange(0, len(value), 2)] 
                    kat.append(''.join([chr(int(v,16)) for v in values]))
                elif attrib == 'MD ':
                    kat.append(value)

            if len(kat) == 3:
                kats.append(tuple(kat))
                kat = []

        f.close()
        self.kats = kats

        return kats
