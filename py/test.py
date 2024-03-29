#!/bin/env python
class Event(object):
    """Representation of an event from the event stream."""

    def __init__(self, id=None, event='message', data='', retry=None):
        self.id = id
        self.event = event
        self.data = data
        self.retry = retry

    def __str__(self):
        s = '{0} event'.format(self.event)
        if self.id:
            s += ' #{0}'.format(self.id)
        if self.data:
            s += ', {0} byte{1}'.format(len(self.data),
                                        's' if len(self.data) else '')
        else:
            s += ', no data'
        if self.retry:
            s += ', retry in {0}ms'.format(self.retry)
        return s

def demo():
    stra = "abcd\nefg\nhijk\n"
    data = b''
    for chunk in stra:
        for line in chunk.splitlines(True):
            if not line.strip():
                yield data
                data = b''
            data += line
    if data:
        yield data
f = demo()
for i in f:
    print i
