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
"""

ITEM_FILE_TEXT = """\
itemToBidOn               sellerUserTest  test BSUser      1 001.00 000.00
"""

TRANSACTION_FILE_TEXT = """\
00 testFSUser      FS 000000.00
"""

EXPECTED_ITEM_FILE_TEXT = """\
itemToBidOn               sellerUserTest  test BSUser      1 001.00 000.00
"""

EXPECTED_USER_FILE_TEXT = """\
"""
EXPECTED_TERMINAL_OUTPUT = ""

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
        
def test_items3():
	try:
		build_files()
		with pytest.raises(Exception, match="Format Error: Item in item file not properly formatted"):
			arg_main(USER_FILE_PATH, ITEM_FILE_PATH, TRANSACTION_FILE_PATH)

	finally:
		# test files must always be deleted
		delete_files()