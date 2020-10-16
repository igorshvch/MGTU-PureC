import re
import random as rd

from writer import writer
from guidialogs import ffp, fdp
from textproc import rwtools


def find_all_word_pairs_ru_en(st):
    st = st.replace('|', ' ')
    return re.findall(r'(?<=<ar>).+?(?=</ar>)', st, flags=re.DOTALL)


def extract_term_def_ru_en(list_of_str):
    res_holder = []
    for item in list_of_str:
        splitted = item.split('\n')
        name = splitted[0]
        name = re.search(r'(?<=>).+?(?=<)', name).group().strip()
        defn = ';'.join(splitted[1:]).strip()
        res_holder.append(name+'|'+defn)
    return res_holder

def extract_term_def_en_ru(list_of_str):
    res_holder = []
    for item in list_of_str:
        if '<tr>' in item:
            splitted = re.split(r'\n<tr>.*?</tr>', item)
            name = splitted[0]
            name = re.search(r'(?<=>).+?(?=<)', name).group().strip()
            defn = splitted[1].replace('\n', ' ').strip()
        else:
            splitted = item.split('\n')
            name = splitted[0]
            name = re.search(r'(?<=>).+?(?=<)', name).group().strip()
            defn = ';'.join(splitted[1:]).strip()      
        res_holder.append(name+'|'+defn)
    return res_holder


def process(text, mode=0):
    options = {
        0: extract_term_def_ru_en,
        1: extract_term_def_en_ru
    }
    p_text = find_all_word_pairs_ru_en(text)
    res_holder = options[mode](p_text)
    rd_res_holder = rd.choices(res_holder, k=20000)
    return rd_res_holder, res_holder, p_text


def find_chars(list_of_strings, char, count):
    for ind, item in enumerate(list_of_strings):
        if item.count(char) > count:
            print(ind, end='||| ')


