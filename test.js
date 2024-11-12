
import { writeFile, readFile } from "file";


var con2 = writeFile('a1.js', "heyyyy 33  yoooo");
print("-----");
con2.then(s=>print(s)).catch(s=>{
    print("here in catch");
    print(s);
});

var con2 = writeFile('a1.js', "heyyyy 33  yoooo");
print("-----");
con2.then(s=>print(s)).catch(s=>print(s));

print("-----");
print("-----");


// var v = myAsyncFunction();
// v.then(s=>print(s)).catch(s=>print(s));
// print("----");

// var v1 = myAsyncFunction();
// v1.then(s=>print(s)).catch(s=>print(s));
// print("----");

var con = readFile('a.js');
print("-----");
con.then(s=>print(s)).catch(s=>print(s));

var con = readFile('a.js');
print("-----");
con.then(s=>print(s)).catch(s=>print(s));

var con = readFile('a.js');
print("-----");
con.then(s=>print(s)).catch(s=>print(s));


// await os.sleepAsync(5);

// var v = myAsyncFunction();
// v.then(s=>print(s)).catch(s=>print(s));
// print("----");

// var v1 = myAsyncFunction();
// v1.then(s=>print(s)).catch(s=>print(s));
// print("----");

// await os.sleepAsync(1);
