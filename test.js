import { a }  from "./a.js";
import * as std from "std";
import { readFile } from "file";

function add(b){
    return a+b;
};

var con = readFile('a.js');
print(add(3,5));