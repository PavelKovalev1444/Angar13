from queue import Queue


class node:
    def __init__(self):
        self.goto = {}
        self.out = []
        self.fail = None


def bor_creation(patterns):
    root = node()
    for pattern in patterns:
        nd = root
        for i in pattern:
            nd = nd.goto.setdefault(i, node())
        nd.out.append(pattern)
    return root    


def create_automat(patterns):
    root = bor_creation(patterns)
    q = Queue()
    #q = []
    for nd in root.goto.values():
        q.put(nd)
        nd.fail = root
    while not q.empty():
        new_nd = q.get(0)
        for key, son_node in new_nd.goto.items():
            q.put(son_node)
            father_node = new_nd.fail
            while father_node is not None and key not in father_node.goto:
                father_node = father_node.fail
            if father_node:
                son_node.fail = father_node.goto[key]
            else:
                son_node.fail = root
            son_node.out += son_node.fail.out
    return root


def pattern_index(patterns, pattern):
    i = 1
    for m in range(len(patterns)):
        if patterns[m] is pattern:
            break
        else:
            i += 1
    return i

def searching(text, patterns, rt):
    nd = rt
    res = []
    for i in range(len(text)):
        while nd is not None and text[i] not in nd.goto:
            nd = nd.fail
        if nd is None:
            nd = rt
            continue
        nd = nd.goto[text[i]]
        for tmp in nd.out:
            res.append([i - len(tmp) + 1, pattern_index(patterns, tmp), tmp])
    return res


def reading(key =0):
    if key:
        print("mode1")
    else:
        pt = []
        text = input()
        n = int(input())
        for i in range(n):
            pt.append(input())
    return [text, pt]


def main():
    data = reading()
    s = data[0]
    patterns = data[1]
    root = create_automat(patterns)
    res = searching(s, patterns, root)
    res.sort()
    #res.sort(key=lambda x: x[0])
    #res.sort(key=lambda x: x[1])
    for i in res:
        print(str(i[0] + 1) + " " + str(i[1]))


if __name__ == '__main__':
    main()