import unittest
import sys

from lr3 import*

class test1(unittest.TestCase):# sorter

	def test1(self):
		self.assertEqual(sorter({'b':[['c', 5, 0]], 'a':[['c', 10, 0],['c', 10,0]],'c':[['d',2 , 0]]}),{'a': [['c', 10, 0], ['c', 10, 0]], 'b': [['c', 5, 0]], 'c': [['d', 2, 0]]})

	def test2(self):
		self.assertEqual(sorter({'b':[['d',10,0],['c', 5, 0]], 'a':[['c', 10, 0],['c', 10,0]],'c':[['d',2 , 0]]}), {'a': [['c', 10, 0], ['c', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]]})

	def test3(self):
		self.assertEqual(sorter({'b':[['d',10,0],['c', 5, 0]], 'a':[['e', 10, 0],['c', 10,0], ['b', 20, 0]],'c':[['d',2 , 0]]}),{'a': [['b', 20, 0], ['c', 10, 0], ['e', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]]})

	def test4(self):
		self.assertEqual(sorter({'d':[['m',2,0]], 'b':[['d',10,0],['c', 5, 0]], 'a':[['e', 10, 0],['c', 10,0], ['b', 20, 0]],'c':[['d',2 , 0]]}), {'a': [['b', 20, 0], ['c', 10, 0], ['e', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]], 'd': [['m', 2, 0]]})

	def test5(self):
		self.assertEqual(sorter({'d':[['m',2,0]], 'b':[['d',10,0]], 'a':[['e', 10, 0],['c', 10,0], ['b', 20, 0]],'c':[['d',2 , 0]]}), {'a': [['b', 20, 0], ['c', 10, 0], ['e', 10, 0]], 'b': [['d', 10, 0]], 'c': [['d', 2, 0]], 'd': [['m', 2, 0]]})


class test2(unittest.TestCase):  # construct_way

	def test1(self):
		self.assertEqual(construct_way({'a': None, 'b': 'a', 'd': 'a', 'e': 'd'}, 'a', 'e'), "ade")

	def test2(self):
		self.assertEqual(construct_way({'a': None, 'b': 'a', 'd': 'a', 'e': 'd', 'f': 'e'}, 'a', 'f'), "adef")

	def test3(self):
		self.assertEqual(construct_way({'m': None, 'd': 'm','k': 'd', 'e': 'k', 'n': 'e'}, 'm', 'n'), "mdken")

	def test4(self):
		self.assertEqual(construct_way({'a': None, 'd': 'a', 't': 'd', 'r': 't', 'p': 'r'}, 'a', 'p'), "adtrp")

	def test5(self):
		self.assertEqual(construct_way({'f': None, 't':'f','a':'t','b': 'a', 'e': 'b', 'd': 'e'}, 'f', 'd'), "ftabed")


class test3(unittest.TestCase):  # bfs

	def test1(self):
		self.assertEqual(bfs({'a': [['c', 10, 0], ['c', 10, 0]], 'b': [['c', 5, 0]], 'c': [['d', 2, 0]]}, 'a', 'd'), {'a': [], 'c': ['a', 10], 'd': ['c', 2]})

	def test2(self):
		self.assertEqual(bfs({'a': [['c', 10, 0], ['c', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]]}, 'a', 'd'), {'a': [], 'c': ['a', 10], 'd': ['c', 2]})

	def test3(self):
		self.assertEqual(bfs({'a': [['c', 10, 0], ['c', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]]}, 'a', 'f'), None)

	def test4(self):
		self.assertEqual(bfs({'a': [['b', 20, 0], ['c', 10, 0], ['e', 10, 0]], 'b': [['d', 10, 0]], 'c': [['d', 2, 0]], 'd': [['m', 2, 0]]}, 'a', 'm'), {'a': [], 'b': ['a', 20], 'c': ['a', 10], 'e': ['a', 10], 'd': ['b', 10], 'm': ['d', 2]})

	def test5(self):
		self.assertEqual(bfs({'a': [['b', 20, 0], ['c', 10, 0], ['e', 10, 0]], 'b': [['c', 5, 0], ['d', 10, 0]], 'c': [['d', 2, 0]], 'd': [['m', 2, 0]]}, 'a', 'm'), {'a': [], 'b': ['a', 20], 'c': ['a', 10], 'e': ['a', 10], 'd': ['b', 10], 'm': ['d', 2]})


class test4(unittest.TestCase):  # find_minimal_capacity

	def test1(self):
		self.assertEqual(find_minimal_capacity({'a': [], 'c': ['a', 10], 'd': ['c', 2]}, 'a', 'd'), 2)

	def test2(self):
		self.assertEqual(find_minimal_capacity({'a': [], 'b':['a',9], 'c': ['b', 10], 'd': ['c', 4]}, 'a', 'd'), 4)

	def test3(self):
		self.assertEqual(find_minimal_capacity({'a': [], 'b':['a',3], 'c': ['b', 10], 'd': ['c', 4]}, 'a', 'd'), 3)

	def test4(self):
		self.assertEqual(find_minimal_capacity({'a': [], 'b':['a',9], 'c': ['b', 10], 'd': ['c', 4], 'e': ['d',1]}, 'a', 'e'), 1)

	def test5(self):
		self.assertEqual(find_minimal_capacity({'a': [], 'b':['a',9], 'c': ['b', 10], 'd': ['c', 4], 'e': ['d', 9]}, 'a', 'e'), 4)

class test5(unittest.TestCase):  # maximum_flow

	def test1(self):
		self.assertEqual(maximum_flow({'a':[['b',8,0,True],['c',8,0,True]], 'b':[['c',1,0,True],['d',1,0,True]], 'c':[['d',8,0,True]]}, 'a', 'd'), [9, ['a', 'b', 1, True], ['a', 'c', 8, True], ['b', 'c', 0, True], ['b', 'd', 1, True], ['b', 'a', 0, False], ['b', 'a', 0, False], ['c', 'd', 8, True], ['c', 'a', 0, False]])

	def test2(self):
		self.assertEqual(maximum_flow({'a':[['b',10,0,True]], 'b':[['c',2,0,True]], 'c':[['d',8,0,True]]}, 'a', 'd'), [2, ['a', 'b', 2, True], ['b', 'c', 2, True], ['b', 'a', 0, False], ['c', 'd', 2, True], ['c', 'b', 0, False]])

	def test3(self):
		self.assertEqual(maximum_flow({'a':[['b',8,0,True], ['c',8,0,True]], 'b':[['c',1,0,True], ['d', 8, 0, True]], 'c':[['d',8,0,True]]}, 'a', 'd'), [16, ['a', 'b', 8, True], ['a', 'c', 8, True], ['b', 'c', 0, True], ['b', 'd', 8, True], ['b', 'a', 0, False], ['b', 'a', 0, False], ['c', 'd', 8, True], ['c', 'a', 0, False]])

	def test4(self):
		self.assertEqual(maximum_flow({'a':[['b',8,0,True], ['c',8,0,True]], 'b':[['c',1,0,True], ['d', 8, 0, True]], 'c':[['e',8,0,True]], 'd':[['f',8,0,True]],'e':[['d', 1, 0, True],['f',8,0,True]]}, 'a', 'f'), [16, ['a', 'b', 8, True], ['a', 'c', 8, True], ['b', 'c', 0, True], ['b', 'd', 8, True], ['b', 'a', 0, False], ['b', 'a', 0, False], ['c', 'e', 8, True], ['c', 'a', 0, False], ['d', 'f', 8, True], ['d', 'b', 0, False], ['e', 'd', 0, True], ['e', 'f', 8, True], ['e', 'c', 0, False], ['e', 'c', 0, False]])

	def test5(self):
		self.assertEqual(maximum_flow({'a':[['b', 1, 0, True], ['c',3,0,True]], 'b':[['c',2,0,True]]}, 'a', 'c'), [4, ['a', 'b', 1, True], ['a', 'c', 3, True], ['b', 'c', 1, True], ['b', 'a', 0, False]])


if __name__ == '__main__':
	unittest.main()