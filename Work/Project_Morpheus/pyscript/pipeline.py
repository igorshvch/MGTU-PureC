import re, sys, ctypes as ct

from guidialogs import ffp, ffps, fdp
from writer import writer
from textproc import rwtools as rw

'''
Define constants for re. routines here:
'''

CLEAN_DOC = r'{}.*{}'.format('-'*66, '-'*66)
FIND_SECTION = r'{}\n.*(?=\n{})'

'''
Wrappers for standart actions
'''

def find_path_to_file():
    '''
    Wrapper for tkinter call
    '''
    return ffp()

def find_all_files_in_directory():
    '''
    Wrapper for tkinter call and files collecting function
    '''
    directory = fdp()
    return rw.collect_exist_files(directory, suffix='.txt')

'''
ctypes routines followed below
'''

def create_dll_connection(dll_path):
    my_c_module = ct.WinDLL(dll_path)
    return my_c_module

def execute_editdist(my_c_module, input_file1, input_file2, output_file):
    my_c_module.compare(
        ct.c_char_p(bytes(input_file1, encoding='cp1251')),
        ct.c_char_p(bytes(input_file2, encoding='cp1251')),
        ct.c_char_p(bytes(output_file, encoding='cp1251'))
    )

def test_my_c_module():
    print("Input dll")
    dll = find_path_to_file()
    print("Input OUT")
    OUT = find_path_to_file()
    print("Input IN1")
    IN1 = find_path_to_file()
    print("Input IN2")
    IN2 = find_path_to_file()
    my_c_module = create_dll_connection(dll)
    print(IN1)
    print(IN2)
    execute_editdist(my_c_module, IN1, IN2, OUT)

def pipeline_editdist():
    print("Input output file path")
    output = find_path_to_file()
    print("Input directory to input files")
    input_files = find_all_files_in_directory()
    print("Input dll path")
    dll = find_path_to_file()
    my_module = create_dll_connection(dll)
    print("OUTPUT: ", output)
    print("DLL ", dll)
    while len(input_files) > 1:
        ref = input_files.pop()
        for item in input_files:
            print("{}|| {} || {}".format(ref, item, output))
            execute_editdist(my_module, str(ref), str(item), str(output))

'''
Some re. routines
found = re.search(r'{}.*?(?={})'.format(content_spl[3], content_spl[4]), text_text, flags=re.DOTALL | re.IGNORECASE).group()
'''

def find_text(text_path):
    with open(text_path) as f:
        text = f.read()
    return text

def clean_text(text, pattern=CLEAN_DOC):
    return re.search(pattern, text, flags=re.DOTALL).group()

def find_contents(contents_path):
    with open(contents_path, mode='r') as f:
        text = f.read()
    contents_spl = [item.strip('\n\t ') for item in text.split('\n') if item]
    return contents_spl + [('-'*66)] #Due to the text structure the final section is ended by '-'*66 line

def section_content_iterator(contents_spl, text):
    for i in range(len(contents_spl)-1):
        if re.search(
            FIND_SECTION.format(contents_spl[i].replace(')', '\)').replace('(', '\('), contents_spl[i+1].replace(')', '\)').replace('(', '\(')),
            text,
            flags=re.DOTALL | re.IGNORECASE):
            yield contents_spl[i], re.search(
                FIND_SECTION.format(contents_spl[i].replace(')', '\)').replace('(', '\('), contents_spl[i+1].replace(')', '\)').replace('(', '\(')),
                text,
                flags=re.DOTALL | re.IGNORECASE
            ).group()
        else:
            yield None, None

def write_contents(contents_spl, text, index=1, prefix="PKP", folder="PKP", verbose=False):
    for ind, (file_name, text) in enumerate(section_content_iterator(contents_spl, text), start=index):
        if file_name:
            writer(
                text,
                '{:04d}_{:s}'.format(ind, file_name.replace('.', '_').replace(' ', '_')),
                mode='w',
                prefix=prefix,
                folder=folder,
                verbose=verbose
            )

def pipeline_content_divide():
    print("Input text path")
    path_text = find_path_to_file()
    print("Input contents path")
    path_content = find_path_to_file()
    text = clean_text(find_text(path_text))
    content_spl = find_contents(path_content)
    write_contents(content_spl, text)

'''
Processing directory
'''

def create_dict_for_file_paths():
    dct = {}
    file_paths = find_all_files_in_directory()
    for path in file_paths:
        path = str(path)
        if re.search(r'PKP \[\d{1,3}\]', path):
            dct.setdefault(re.search(r'PKP \[\d{1,3}\]', path).group(), []).append(path)
        else:
            print("ERROR!", path)
    return dct

def pipeline_for_directory():
    print("Input directory path")
    dct_with_paths = create_dict_for_file_paths()
    for key in dct_with_paths:
        try:
            path_text, path_content = dct_with_paths[key]
            text = clean_text(find_text(path_text))
            content_spl = find_contents(path_content)
            write_contents(content_spl, text, prefix=key, folder="PKP_new_test")
        except:
            print("ERROR!", path_text, path_content)

'''
Miscellaneous
'''

def num_of_comparisons(n):
    i = 0
    while n:
        i+=n
        n-=1
    return i

def estimate(n, st='s'):
    st = st
    res = ""
    count1 = 51
    count2 = 0
    while n:
        count2 = sys.getsizeof(res)
        print(count2, count1, count2-count1, end=' ')
        if ((count2-count1)>1):
            print("\tЗамечена разница более 1!")
        else:
            print()
        count1 = count2
        res += st
        n -= 1