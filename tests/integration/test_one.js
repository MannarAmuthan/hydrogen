import { readFile } from "file";

function assert(valueOne, valueTwo, func_name){
    if(valueOne == valueTwo){
        print("Assertion passed in : "+func_name);
        return true;
    }
    print("Assertion failed in : "+func_name);
    throw -1;
}

async function test_should_read_from_file(){
        var actual = await readFile("tests/integration/text_file.txt");
        var expected = "Hydrogen is a chemical element; it has symbol H and atomic number 1. It is the lightest element and, at standard conditions, is a gas of diatomic molecules with the formula H2, sometimes called dihydrogen,[11] but more commonly called hydrogen gas, molecular hydrogen or simply hydrogen. It is colorless, odorless,[12] non-toxic, and highly combustible. Constituting about 75% of all normal matter, hydrogen is the most abundant chemical element in the universe.[13][note 1] Stars, including the Sun, mainly consist of hydrogen in a plasma state, while on Earth, hydrogen is found in water, organic compounds, as dihydrogen, and in other molecular forms. The most common isotope of hydrogen (protium, 1H) consists of one proton, one electron, and no neutrons."

        assert(actual, expected, "test_should_read_from_file");
}

try{
   await test_should_read_from_file();
}
catch(e){
    print("Tests failed");
}

