import { a }  from "./a.js";
import * as std from "std";

function add(b){
    return a+b;
};

if(std.loadFile('a.js')){
    print(std.loadFile('a.js'));
}

print(add(3,5));