
import { writeFile, readFile } from "file";
import {a} from 'a.js'

import {get, createServer} from 'http'
import {Point, createPoint} from 'point'




print( new Point(4,5).x);
print( createPoint(4,5).x);

var server = createServer();
server.serve();
// print(server);
// get("example.com").then ((r) => {
//     print(r);
//     print("Response-----");
// }).catch((e)=> {
//     print(e);
// });

// var con2 = writeFile('a1.js', "heyyyy 33  yoooo");
// print("-----");
// con2.then(s=>print(s)).catch(s=>{
//     print("here in catch");
//     print(s);
// });

// var con2 = writeFile('a1.js', "heyyyy 33  yoooo");
// print("-----");
// con2.then(s=>print(s)).catch(s=>print(s));

// print("-----");
// print("-----");


// // var v = myAsyncFunction();
// // v.then(s=>print(s)).catch(s=>print(s));
// // print("----");

// // var v1 = myAsyncFunction();
// // v1.then(s=>print(s)).catch(s=>print(s));
// // print("----");

var con = await readFile('a.js');
print(con);
// con.then(s=>print(s)).catch(s=>print(s));

// var con = readFile('a.js');
// print("-----");
// con.then(s=>print(s)).catch(s=>print(s));

// var con = readFile('a.js');
// print("-----");
// con.then(s=>print(s)).catch(s=>print(s));


// // await os.sleepAsync(5);

// // var v = myAsyncFunction();
// // v.then(s=>print(s)).catch(s=>print(s));
// // print("----");

// // var v1 = myAsyncFunction();
// // v1.then(s=>print(s)).catch(s=>print(s));
// // print("----");

// // await os.sleepAsync(1);
