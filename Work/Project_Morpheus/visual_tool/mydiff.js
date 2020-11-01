function LCS_Length(norm_text1, norm_text2) {
    let m = norm_text1.length;
    let n = norm_text2.length;
    let i, j;
    let c = new Array(m+1);
    let b = new Array(m+1);
    for (i=0; i<m+1; i++) {
        c[i] = new Array(n+1);
        b[i] = new Array(n+1);
        for(j=0; j<n+1; j++) {
            c[i][j] = 0;
            b[i][j] = 0;
        }
    }
    for (i=1; i<m+1; i++) {
        for (j=1; j<n+1; j++) {
            if (norm_text1[i-1] === norm_text2[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 'DIOG';
            }
            else {
                if (c[i-1][j] >= c[i][j-1]) {
                    c[i][j] = c[i-1][j]
                    b[i][j] = 'UP'
                }
                else {
                    c[i][j] = c[i][j-1]
                    b[i][j] = 'LEFT'
                }
            }
        }
    }
    return [c[m][n], b]
}

function return_LCS_num(result_b_table, norm_text1, len_norm_text1, len_norm_text2, num_box1, num_box2) {
    if (len_norm_text1 === 0 || len_norm_text2 === 0){
        return null;
    }
    if (result_b_table[len_norm_text1][len_norm_text2] === 'DIOG') {
        return_LCS_num(result_b_table, norm_text1, len_norm_text1-1, len_norm_text2-1, num_box1, num_box2);
        num_box1.push(len_norm_text1-1);
        num_box2.push(len_norm_text2-1);
    } else if (result_b_table[len_norm_text1][len_norm_text2] === 'UP') {
        return_LCS_num(result_b_table, norm_text1, len_norm_text1-1, len_norm_text2, num_box1, num_box2);
    } else {
        return_LCS_num(result_b_table, norm_text1, len_norm_text1, len_norm_text2-1, num_box1, num_box2);
    }
}

function LCS_main(str1, str2) {
    console.log("Action2");
    let i, len; //int
    str1 = str1.replace(/\n/g, ' rr ');
    str2 = str2.replace(/\n/g, ' rr ');
    let arr1 = str1.replace(/[^А-я0-9-/#@N()r\.,;]/g, " ").split(" ");
    let arr2 = str2.replace(/[^А-я0-9-/#@N()r\.,;]/g, " ").split(" ");
    let len_arr1 = arr1.length;
    let len_arr2 = arr2.length;
    let len_LCS, result_b_table;
    [len_LCS, result_b_table] = LCS_Length(arr1, arr2);
    let num_box_arr1 = [];
    let num_box_arr2 = []; //arrays
    let result_arr1 = [];
    let result_arr2 = []; //arrays
    let res_str1, res_str2; //strings
    let newliner = "<br>";
    return_LCS_num(result_b_table, arr1, len_arr1, len_arr2, num_box_arr1, num_box_arr2);
    if (len_arr1 === len_arr2 && len_arr2 === len_LCS)
        return ['<span class="equal">'+'Отрывки идентичны'+'</span>', '<span class="equal">'+'Отрывки идентичны'+'</span>', len_arr1, len_arr2, 100];
    else {
        result_arr1 = Array.from(arr1);
        result_arr2 = Array.from(arr2);
        for (i=0, len=result_arr1.length; i<len; i++)
            if (!num_box_arr1.includes(i)) {
                let temp = result_arr1[i];
                result_arr1[i] = (temp === "rr" ? newliner : '<span class="del">'+temp+'</span>');
            }
        for (i=0, len=result_arr2.length; i<len; i++)
            if (!num_box_arr2.includes(i)) {
                let temp = result_arr2[i];
                result_arr2[i] = (temp === "rr" ? newliner: '<span class="new">'+temp+'</span>');
            }
        res_str1 = result_arr1.join(' ');
        res_str2 = result_arr2.join(' ');
        res_str1 = res_str1.replace(/rr/g, "<br>");
        res_str2 = res_str2.replace(/rr/g, "<br>");
        console.log(len_LCS);
        console.log(len_arr1);
        console.log(len_arr2);
        console.log(len_LCS/len_arr1);
        console.log(len_LCS/len_arr2);
        return [res_str1, res_str2, len_arr1, len_arr2, ((len_arr1>len_arr2 ? (len_LCS/len_arr1):(len_LCS/len_arr2))*100).toFixed(2)];
    }
}
