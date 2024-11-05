// import { a }  from "./a.js";
import * as os from "os";
import { readFile, writeFile } from "file";
import { myAsyncFunction } from "test";

var con = readFile('a.js');
print("-----");
con.then(s=>print(s)).catch(s=>print(s));




var con2 = writeFile('a1.js', "heyyyy 33  yoooo");
print("-----");
con2.then(s=>print(s)).catch(s=>print(s));

print("-----");
print("-----");

var v = myAsyncFunction();
v.then(s=>print(s)).catch(s=>print(s));
print("----");
