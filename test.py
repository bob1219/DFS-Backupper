from subprocess import check_output
from sys import exit
try:
    print('clear:')
    check_output('backup clear test')
    print('ok.')
    print()

    print('add:')
    check_output('backup add test -f a.txt b.txt')
    check_output('backup add test -f dummy1 dummy2')
    check_output('backup add test -d abc def')
    check_output('backup add test -d dummy3 dummy4')
    print('ok.')
    print()

    print('remove:')
    check_output('backup remove test -f dummy1 dummy2')
    check_output('backup remove test -d dummy3 dummy4')
    print('ok.')
    print()

    print('list:')
    check_output('backup list test')
    print('ok.')
    print()

    print('run:')
    check_output('backup run test')
    print('ok.')
    print()

    print('test successful')
    exit(0)
except:
    print('test failed')
    exit(1)
