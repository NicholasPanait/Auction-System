import os
import sys
import pytest
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
# allows us to import python files in parent directory
# EG
from main import *


USER_FILE_PATH = '_test_users.txt'
ITEM_FILE_PATH = '_test_items.txt'
TRANSACTION_FILE_PATH = '_test_transaction.txt'
# Note, do not indent mutli line strings, else they will be indented in the file causing issues.
USER_FILE_TEXT = """\
testAAUser      AA 000000.00 password
testBSUser      BS 000000.00 password
testFSUser      FS 000000.00 password
testSSUser      SS 000000.00 password
testingBuyer    BS 010000.00 password
testingSeller   SS 010000.00 password
sellerUserTest  SS 000000.00 password
buyUserTest     BS 000000.00 password
"""

ITEM_FILE_TEXT = """\
itemToBidOn              sellerUserTest  testBSUser      10 001.00 000.00
"""

TRANSACTION_FILE_TEXT = """\
02                 SS 000000.00 420
00 testAAUser      AA 000000.00
"""

EXPECTED_ITEM_FILE_TEXT = """\
itemToBidOn              sellerUserTest  testBSUser      10 001.00 000.00
"""

EXPECTED_USER_FILE_TEXT = """\
testAAUser      AA 000000.00 password
testBSUser      BS 000000.00 password
testFSUser      FS 000000.00 password
testSSUser      SS 000000.00 password
testingBuyer    BS 010000.00 password
testingSeller   SS 010000.00 password
sellerUserTest  SS 000000.00 password
buyUserTest     BS 000000.00 password
"""
EXPECTED_TERMINAL_OUTPUT = "Error: Incorrect formatting for Delete in Daily Transaction File\n"

def build_files():
	with open(USER_FILE_PATH, 'wt') as file:
		file.write(USER_FILE_TEXT)
	with open(ITEM_FILE_PATH, 'wt') as file:
		file.write(ITEM_FILE_TEXT)
	with open(TRANSACTION_FILE_PATH, 'wt') as file:
		file.write(TRANSACTION_FILE_TEXT)


def delete_files():
	if os.path.exists(USER_FILE_PATH):
		os.remove(USER_FILE_PATH)
	if os.path.exists(ITEM_FILE_PATH):
		os.remove(ITEM_FILE_PATH)
	if os.path.exists(TRANSACTION_FILE_PATH):
		os.remove(TRANSACTION_FILE_PATH)


def test_delete2(capsys):
	#PUT TEST CODE HERE, example is a system test
	try:
		build_files()
		
		arg_main(USER_FILE_PATH,ITEM_FILE_PATH,TRANSACTION_FILE_PATH)

		with open(USER_FILE_PATH, "rt") as file:
			assert file.read() == EXPECTED_USER_FILE_TEXT
		with open(ITEM_FILE_PATH, "rt") as file:
			assert file.read() == EXPECTED_ITEM_FILE_TEXT

		assert capsys.readouterr().out == EXPECTED_TERMINAL_OUTPUT

	finally:
		# test files must always be deleted
		delete_files()