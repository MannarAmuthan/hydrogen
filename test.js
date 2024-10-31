import { a }  from "./a.js";
import * as std from "std";
import { readFile, writeFile } from "file";

function add(b){
    return a+b;
};

var con = readFile('a.js');

writeFile('b1.js', 'my');
print(add(3,5));