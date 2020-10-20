import re, sys, ctypes as ct

from guidialogs import ffp, ffps, fdp
from writer import writer
from textproc import rwtools as rw

'''
Some common func_args and innre_vars names whis are consitently used throughout whis module:
path_to_text
path_to_content
section_pattern
content_spl
'''

###############################################################################
###############################################################################
'''
Define constants for re. routines here:
'''
###############################################################################
###############################################################################

CLEAN_DOC = r'{}.*{}'.format('-'*66, '-'*66)
FIND_SECTION = r'\n{}.*?(?=\n{})' #r'{}\n.*?(?=\n{}\n)'

###############################################################################
###############################################################################
'''
Wrappers for standart actions
'''
###############################################################################
###############################################################################

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

###############################################################################
###############################################################################
'''
ctypes routines followed below
'''
###############################################################################
###############################################################################

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

###############################################################################
###############################################################################
'''
Some re. routines
found = re.search(r'{}.*?(?={})'.format(content_spl[3], content_spl[4]), text_text, flags=re.DOTALL | re.IGNORECASE).group()
'''
###############################################################################
###############################################################################

def find_text(text_path):
    with open(text_path) as f:
        text = f.read()
    return text

def clean_text(text, pattern=CLEAN_DOC):
    return re.search(pattern, text, flags=re.DOTALL).group()

def find_content(path_to_content):
    with open(path_to_content, mode='r') as f:
        text = f.read()
    content_spl = [item.strip('\n\t ') for item in text.split('\n') if item]
    return content_spl + [('-'*66)] #Due to the text structure the final section is ended by '-'*66 line

def section_content_iterator(content_spl, text):
    start = 0
    inner_text = text
    for i in range(len(content_spl)-1):
        inner_text = inner_text[start:]
        match = re.search(
            FIND_SECTION.format(content_spl[i].replace(')', '\)').replace('(', '\('), content_spl[i+1].replace(')', '\)').replace('(', '\(')),
            inner_text,
            flags=re.DOTALL | re.IGNORECASE
        )
        if match:
            yield content_spl[i], match.group()
            start = match.end()
        else:
            yield None, None

def write_content(content_spl, text, index=1, prefix="PKP", folder="PKP", verbose=False):
    for ind, (file_name, text) in enumerate(section_content_iterator(content_spl, text), start=index):
        if file_name:
            writer(
                text,
                '{:04d}_{:s}'.format(ind, file_name[:25].replace('.', '_').replace(' ', '_')),
                mode='w',
                prefix=prefix,
                folder=folder,
                verbose=verbose
            )

###############################################################################
###############################################################################
'''
Processing directory
'''
###############################################################################
###############################################################################

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

###############################################################################
###############################################################################
'''
Pipelines
'''
###############################################################################
###############################################################################

def pipeline_content_divide():
    print("Input text path")
    path_text = find_path_to_file()
    print("Input content path")
    path_content = find_path_to_file()
    text = clean_text(find_text(path_text))
    content_spl = find_content(path_content)
    write_content(content_spl, text)

def pipeline_for_directory():
    print("Input directory path")
    dct_with_paths = create_dict_for_file_paths()
    for key in dct_with_paths:
        try:
            path_text, path_content = dct_with_paths[key]
            text = clean_text(find_text(path_text))
            content_spl = find_content(path_content)
            write_content(content_spl, text, prefix=key, folder="PKP_new_test_3")
        except:
            print("ERROR!", path_text, path_content)

###############################################################################
###############################################################################
'''
Process results
'''
###############################################################################
###############################################################################

def find_top_best(threshold):
    holder = list()
    file_r = open(ffp(), mode='r')
    for ind, line in enumerate(file_r):
        if line and line != '\n':
            spl = line[:-1].split('|')
            spl[-1] = float(spl[-1].replace(',', '.'))
            if spl[-1] > threshold:
                holder.append(spl)
            if (ind % 500000 == 0):
                print("Lines processed: {:7d}".format(ind))
    file_r.close()
    return holder

'''
holder_srt = sorted(holder, key=lambda x: x[-1], reverse = True)

for item in holder_srt:
    dct.setdefault(item[0], []).extand(item[1:])

from collections import Counter

leng = [len(dct[key]) for key in dct]
cn = Counter(leng)
cn.most_common(30)
'''

def create_dct_of_doc_names():
    doc_names = str()
    doc_spl = list()
    dct = dict()
    with open(ffp(), mode='r') as f:
        doc_names = f.read()
    doc_spl = [item.split('|') for  item in doc_names.split('\n')]
    dct = {key:val for key,val in doc_spl}
    return dct

def create_content_for_doc():
    res_dct = dict()
    print("Input path to docs list")
    doc_dct = create_dct_of_doc_names()
    print("Input directory path")
    dct_with_paths = create_dict_for_file_paths()
    for key in doc_dct:
        try:
            name = doc_dct[key]
            _, path_content = dct_with_paths[key]
            content_spl = find_content(path_content)
            content_spl = [
                ('{:s}'.format(key), '{:04d}'.format(ind), '{:s}'.format(item))
                for ind, item
                in enumerate(content_spl, start=1)
            ]
            res_dct[name] = content_spl[:-1]
        except:
            print("ERROR!", key, name, path_content)
    return res_dct

def create_total_content():
    res_list = list()
    print("Input path to docs list")
    doc_dct = create_dct_of_doc_names()
    print("Input directory path")
    dct_with_paths = create_dict_for_file_paths()
    for key in doc_dct:
        try:
            name = doc_dct[key]
            _, path_content = dct_with_paths[key]
            content_spl = find_content(path_content)
            content_spl = [
                ('{:s}'.format(key), '{:04d}'.format(ind), '{:s}'.format(item))
                for ind, item
                in enumerate(content_spl, start=1)
            ]
            res_list += content_spl[:-1]
        except:
            print("ERROR!", key, name, path_content)
    return res_list

def create_result_table(all_content_lst, best_res_lst):
    dct_res = dict()
    search_str = str()
    for item_cnt in all_content_lst:
        key, ind, content_item = item_cnt
        search_str = '{:s}_{:s}'.format(key, ind)
        for item_br in best_res_lst:
            path_file1, _, path_file2, _, _, rank = item_br
            if search_str in path_file1:
                dct_res.setdefault(key, []).append([content_item, path_file2, rank])
            if search_str in path_file2:
                dct_res.setdefault(key, []).append([content_item, path_file1, rank])
    return dct_res

def create_result_table2(all_content_lst, best_res_lst, dct_with_cnt, dct_with_docs_names):
    dct_res = dict()
    holder_res = list()
    #search_str = str()
    for indd, item_cnt in enumerate(all_content_lst):
        if (indd % 250 == 0):
            print("Processed item: {:4d}".format(indd))
        key, ind, content_item = item_cnt
        #search_str = '{:s}_{:s}'.format(key, ind)
        for indd2, item_br in enumerate(best_res_lst):
            path_file1, _, path_file2, _, _, rank = item_br
            path_file1 = path_file1.split('/')[-1].split('_')[:4]
            path_file2 = path_file2.split('/')[-1].split('_')[:4]
            if ind == path_file1[-1] and key == path_file1[-2]:
                try:
                    '''
                    dct_res.setdefault((key, dct_with_docs_names[key]), []).append(
                        [
                            content_item,
                            path_file2[-2],
                            dct_with_docs_names[path_file2[-2]],
                            dct_with_cnt[(path_file2[-2], path_file2[-1])],
                            rank
                        ]
                    )
                    '''
                    holder_res.append(
                        [
                            key,
                            dct_with_docs_names[key],
                            ind,
                            content_item,
                            path_file2[-2],
                            dct_with_docs_names[path_file2[-2]],
                            path_file2[-1],
                            dct_with_cnt[(path_file2[-2], path_file2[-1])],
                            rank
                        ]
                    )
                except:
                    print("ERROR! {}-{}->CND1, {}".format(indd, indd2, path_file2[-2]))
                    print(path_file2)
                    print(item_cnt)
                    print(item_br)
                    print()
            if ind == path_file2[-1] and key == path_file2[-2]:
                try:
                    '''
                    dct_res.setdefault((key, dct_with_docs_names[key]), []).append(
                        [
                            content_item,
                            path_file1[-2],
                            dct_with_docs_names[path_file1[-2]],
                            dct_with_cnt[(path_file1[-2], path_file1[-1])],
                            rank
                        ]
                    )
                    '''
                    holder_res.append(
                        [
                            key,
                            dct_with_docs_names[key],
                            ind,
                            content_item,
                            path_file1[-2],
                            dct_with_docs_names[path_file1[-2]],
                            path_file1[-1],
                            dct_with_cnt[(path_file1[-2], path_file1[-1])],
                            rank
                        ]
                    )
                except:
                    print("ERROR! {}-{}->CND2, {}".format(indd, indd2, path_file1[-2]))
                    print(path_file1)
                    print(item_cnt)
                    print(item_br)
                    print()
    return dct_res, holder_res

'''
rl = pl.create_total_content()

dct_with_cnt = {(st1, st2):st3 for (st1, st2, st3) in rl}

dct_with_docs_names = create_dct_of_doc_names()

DR, RL = pl.create_result_table2(rl, holder, dct_with_cnt, dct_with_docs_names)

DR, RL = pl.create_result_table2(rl, holder, rl_d, dn)

import locale
locale.setlocale(locale.LC_ALL, '')
RL2 = [item[:-1] + ['{:n}'.format(item[-1])] for item in RL

writer(('|'.join([str(i) for i in item]) for item in RL2), 'test_final_results_2', mode='w')
'''

###############################################################################
###############################################################################
'''
Miscellaneous
'''
###############################################################################
###############################################################################

def num_of_comparisons(n):
    i = 0
    while n:
        i+=n
        n-=1
    return i

def estimate(n, st='s'):
    '''
    Count memory for string object depending on differnet string sizes and different languages
    '''
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

###############################################################################
###############################################################################
'''
Tests
'''
###############################################################################
###############################################################################

def test_section_content_iterator(content_spl, text, pattern=FIND_SECTION):
    start = 0
    inner_text = text
    for i in range(len(content_spl)-1):
        inner_text = inner_text[start:]
        match = re.search(
            pattern.format(content_spl[i].replace(')', '\)').replace('(', '\('), content_spl[i+1].replace(')', '\)').replace('(', '\(')),
            inner_text,
            flags=re.DOTALL | re.IGNORECASE
        )
        if match:
            yield content_spl[i], match.group(), start
            start = match.end()
        else:
            yield None, None, None

def test_write_content(content_spl, text, index=1, prefix="PKP", folder="PKP", verbose=False):
    for ind, (file_name, text, start) in enumerate(test_section_content_iterator(content_spl, text), start=index):
        if file_name:
            writer(
                text,
                '{:04d}_{:s}'.format(ind, file_name[:25].replace('.', '_').replace(' ', '_')),
                mode='w',
                prefix=prefix,
                folder=folder,
                verbose=verbose
            )
            print('{:04d}_{:200s}'.format(ind, file_name.replace('.', '_').replace(' ', '_')), '\t', start)

class TestContentDivider():
    def __init__ (self, path_to_text, path_to_content, section_pattern=FIND_SECTION):
        self.path_to_text = path_to_text
        self.path_to_content = path_to_content
        self.text = str()
        self.content_spl = list()
        self.dct_cnt_txt = dict()
        self.section_pattern = section_pattern
    
    def self_exam(self):
        print("self.section_pattern =", self.section_pattern)
        if self.path_to_text:
            print("self.path_to_text =", self.path_to_text)
        if self.path_to_content:
            print("self.path_to_content=", self.path_to_content)
        if self.text:
            print("self.text IS SET")
        if self.content_spl:
            print("self.content_spl IS SET")
        if self.dct_cnt_txt:
            print("self.dct_cnt_txt IS SET")

    def process(self):
        self.content_spl = find_content(self.path_to_content)
        with open(self.path_to_text, mode='r') as f:
            self.text = f.read()
        self.write_content_to_dict()
        
    def write_content_to_dict(self):
        dct = dict()
        for ind, (file_name, text, start) in enumerate(self.test_section_content_iterator(), start=1):
            if file_name:
                dct['{:04d}_{:s}'.format(ind, file_name[:25].replace('.', '_').replace(' ', '_'))] = [
                    text,
                    start,
                    len(text)
                ]
            else:
                print("ERROR! {}, {}", ind, file_name)
        self.dct_cnt_txt = dct
    
    def test_section_content_iterator(self):
        start = 0
        inner_text = self.text
        content_spl = self.content_spl
        pattern = self.section_pattern
        for i in range(len(content_spl)-1):
            inner_text = inner_text[start:]
            match = re.search(
                pattern.format(
                    self.content_spl[i].replace(')', '\)').replace('(', '\('),
                    self.content_spl[i+1].replace(')', '\)').replace('(', '\(')
                ),
                inner_text,
                flags=re.DOTALL | re.IGNORECASE
            )
            if match:
                yield content_spl[i], match.group(), start
                start = match.end()
            else:
                yield None, None, None

def test_total_num_of_created_contents():
    counter = 0
    print("Input directory path")
    dct_with_paths = create_dict_for_file_paths()
    for key in dct_with_paths:
        try:
            _, path_content = dct_with_paths[key]
            content_spl = find_content(path_content)
            counter += (len(list(content_spl)) - 1)
        except:
            print("ERROR!", _, path_content)
    print("Total sections: ", counter)
