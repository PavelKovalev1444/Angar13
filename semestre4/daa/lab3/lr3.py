import queue
 
 
def maximum_flow(graph, startVertex, endVertex):
    f = 0
    while (True):
        dway = bfs(graph, startVertex, endVertex)
        if (dway is None):
            break
        way = construct_way(dway, startVertex, endVertex)
        cmin = find_minimal_capacity(dway, startVertex, endVertex)
        f += cmin
        for i in range(0, len(way) - 1):
            for m in graph[way[i]]:
                if m[0] is way[i + 1]:
                    if way[i+1] != endVertex:
                        for a in graph[way[i + 1]]:
                            if a[0] is way[i]:
                                a[1] += cmin
                                a[2] -= cmin
                                if a[3]:
                                    a[3] = True
                                else:
                                    a[3] = False
                                break
                            else:
                                graph.setdefault(way[i + 1], []).append([way[i], cmin, 0, False])
                    m[1] -= cmin
                    m[2] += cmin
    res = [f]
    for i in graph:
        for m in graph[i]:
            if(m[2] < 0):
                res.append([i, m[0], 0, m[3]])
            else:
                res.append([i, m[0], m[2], m[3]])
    return res
 
 
def find_minimal_capacity(dway, startVertex, endVertex):
    tmpKey = endVertex
    cmin = dway[tmpKey][1]
    while dway[tmpKey][0] != startVertex:
        tmpVal = dway[tmpKey][0]
        if (cmin > dway[tmpVal][1]):
            cmin = dway[tmpVal][1]
        tmpKey = tmpVal
    return cmin
 
 
def bfs(graph, startV, endV):
    q = queue.Queue()
    q.put(startV)
    paths = {startV: []}
    while (not q.empty()):
        vertex = q.get()
        if vertex in graph:
            for v in graph[vertex]:
                if (v[1] > 0 and v[0] not in paths):
                    paths[v[0]] = [vertex, v[1]]
                    if v[0] == endV:
                        return paths
                    q.put(v[0])
    return None
 
 
def construct_way(dict_way, start, end):
    way = ""
    tmpKey = end
    way += tmpKey
    while dict_way[tmpKey][0] != start:
        tmpVal = dict_way[tmpKey][0]
        way += tmpVal
        tmpKey = tmpVal
    way += start
    return way[::-1]
 
 
def sorter(diction):
    key_list = list(diction.keys())
    key_list.sort()
    items_list = []
    for i in range(len(key_list)):
        items_list.append(diction[key_list[i]])
    for i in items_list:
        i.sort(key=lambda x: x[0])
    d = {}
    for i in key_list:
        r = []
        for m in items_list:
            if m == diction[i]:
                r.append(m)
        d[i] = r[0]
    return d
 
 
def main():
    n = int(input())
    startVertex = input()
    endVertex = input()
    d = {}
    m = []
    while (n > 0):
        s = input().split()
        m.append(s)
        d.setdefault(s[0], []).append([s[1], int(s[2]), 0, True])
        n -= 1
    d = sorter(d)
    result = maximum_flow(d, startVertex, endVertex)
    flow = result[0]
    l = []
    for i in result:
        if i != flow:
            l.append(i)
    l.sort(key=lambda x: x[0])
    print(flow)
    for i in range(0, len(l)):
        if l[i][3]:
            s = ""
            for m in range(len(l[i])-1):
                s += str(l[i][m]) + " "
            num = len(s)
            print(s[0:num - 1:1])
 
 
if __name__ == '__main__':
    main()