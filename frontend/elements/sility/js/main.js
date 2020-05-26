// var csvStringState = [`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 1,0,0,0,0,0,0,0,0,0,0,0
// ,,,,1,0,0,0,0,,,
// ,,,,2,0,0,0,0,,,
// ,,,,3,0,0,0,0,,,
// ,,,,4,0,0,0,0,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,0,1,0,0,0,0,0,0,0,0,0
// 1,1,0,0,1,0,0,0,0,,,
// ,,,,2,0,0,0,0,,,
// ,,,,3,0,0,0,0,,,
// ,,,,4,0,0,0,0,,,`,
// `matrizCreada ,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,0,0,1,0,0,0,0,0,0,0,0
// 0,1,0,1,1,0,0,0,0,,,
// 1,2,0,0,2,0,0,0,0,,,
// ,,,,3,0,0,0,0,,,
// ,,,,4,0,0,0,0,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,,0,0,0,1,0,0,0,0,0,0
// 0,,0,0,1,0,0,0,0,,,
// 0,2,0,0,2,0,0,0,0,,,
// 1,3,0,0,3,0,0,0,0,,,
// ,,,,4,0,0,0,0,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,,0,0,0,1,0,0,0,0,0,0
// 0,,0,0,1,0,0,0,0,,,
// 0,2,1,0,2,0,0,0,0,,,
// 0,3,0,0,3,0,0,0,0,,,
// 1,4,0,0,4,0,0,0,0,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,,0,0,0,0,1,0,0,0,0,0
// 0,,0,0,1,0,0,0,0,,,
// 0,2,0,1,2,0,0,0,0,,,
// 0,3,0,0,3,0,0,0,0,,,
// 0,4,0,1,4,0,0,0,0,,,
// 1,5,0,,,,,,,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,,0,0,0,0,0,0,0,0,1,0
// 0,,0,0,1,1,0,0,0,,,
// 0,,0,0,2,0,0,0,0,,,
// 0,3,1,0,3,0,0,0,0,,,
// 0,,0,0,4,0,0,0,0,,,
// 0,5,0,,,,,,,,,
// 1,6,0,,,,,,,,,`,
// `matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
// 0,,0,0,0,0,0,0,0,1,1,0
// 0,,0,0,1,0,0,0,1,,,
// 0,,0,0,2,0,0,0,0,,,
// 0,3,0,1,3,0,0,0,0,,,
// 0,,0,0,4,0,0,0,0,,,
// 0,5,0,0,,,,,,,,
// 0,6,0,1,,,,,,,,`]; 

// d3.csv("./simul.csv").then(function(data) {
//     console.log(data[0]);
//   });


var csvStringState;
async function readTextFile()
{
    await fetch('http://localhost:5000/prueba.txt', {mode: 'no-cors'})
    .then(response => response.text())
    .then(data=> {
        var someText = data.replace(/(\r\n|\n|\r)/gm, "\n" );
        csvStringState = someText.split("`");
        console.log(typeof (csvStringState));
        console.log(csvStringState);
    })
    .catch(error => console.error(error));
}


// var csvStringState = readTextFile();
var objeto = {};
var csvConfig = {
    noheader:false,
    trim:true}

    function createPro(nProces)
    {
        for (let index = 0; index < nProces; index++) 
        {
            $(".bolas").append("<div id = 'procesador' class = 'bola_p1'></div>");
        }
    }

    function createMat()
    {
            $(".matrices").append("<span class='dot'></span>");
    }

    function writeNum(clase,n, tag1, tag2)
    {
        $( clase ).replaceWith( tag1+ n + tag2 );
    }

    function resolveAfter1Seconds() {
        return new Promise(resolve => {
          setTimeout(() => {
            resolve('resolved');
          }, 1000);
        });
      }

async function Simulation() {
    await readTextFile();
    console.log(csvStringState[0])
    const stateArrayInit=await csv(csvConfig).fromString(csvStringState[0]);
    console.log("stateArrayInit " + stateArrayInit.length);
    var nProces = stateArrayInit.length;
    console.log("nProces " + nProces);
    createPro(nProces);
    for (let index = 0; index < csvStringState.length; index++) {
        
            console.log("State it: " + index);
            const stateArray=await csv(csvConfig).fromString(csvStringState[index]);
            //console.log(stateArray);

            if(stateArray.length != 0 )
            {
                console.log(stateArray);
            nodeList = document.querySelectorAll("div.bola_p1");
            for (let k = 0; k < stateArrayInit.length; k++) {
                    if (fail == true) {
                    var num = countF;
                    writeNum(".numF",num,"<h4 class=numF>","</h4>");
                    fail = false;
                    }

                    if (stateArray[k].working == 0 && stateArray[k].rc == 0 && stateArray[k].rb == 0) {
                        nodeList[k].style.backgroundColor = "red";
                    }else if(stateArray[k].working == 1){
                        nodeList[k].style.backgroundColor = "green";
                    }else if(stateArray[k].rc == 1 && stateArray[k].rb == 0){
                        nodeList[k].style.backgroundColor = "yellow";
                        writeNum(".sign","RC","<div class = sign>","</div>");
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        writeNum(".sign","","<div class = sign>","</div>");
                        fail = true;
                        ++countF; 
                    }else if(stateArray[k].rc == 0 && stateArray[k].rb == 1){
                        nodeList[k].style.backgroundColor = "yellow";
                        writeNum(".sign","RB","<div class = sign>","</div>");
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        writeNum(".sign","","<div class = sign>","</div>");
                    }
                    if (stateArray[k].finish == 1) {
                         ++countC;
                        var num = countC;
                        writeNum(".numC",num,"<h4 class=numC>","</h4>");                     
                    }
                    
                    
                }
        }else{
            console.log("nada");
        }
        if(stateArray.length != 0 )
        {
            for (let k = 0; k < stateArray.length; k++) {
                if (stateArray[k].matrizCreada == "") {
                    console.log("nada");
                }else if(stateArray[k].idMatriz == k && stateArray[k].matrizCreada == "1" ){
                    await resolveAfter1Seconds();
                    console.log("crear");
                    createMat(1);
                }else{
                    nodeListM = document.querySelectorAll(".dot");
                    if (stateArray[k].hold == "1") {
                        await resolveAfter1Seconds();
                        console.log("Hold:" + stateArray[k].idMatriz);
                        nodeListM[k].style.backgroundColor = "purple";
                        countH++;
                        hold = true;
                        writeNum(".numT",countH,"<h4 class=numT>","</h4>" );
                    }else if (stateArray[k].mult == "1") {
                        nodeListM[k].style.backgroundColor = "blue";
                        if(hold == true)
                        {
                            countH-=1;
                            hold = false
                            writeNum(".numT",countH,"<h4 class=numT>","</h4>" );
                        }
                        console.log("Mult:" + stateArray[k].idMatriz);
                    }else if ((stateArray[k].idMatriz == "" && stateArray[k].matrizCreada == "0")) {
                        console.log("borrar " + stateArray[k].idMatriz);
                        nodeListM[k].style.backgroundColor = "black";
                    }
                }
            }
                
    
        }else{
            console.log("nada");
        }

    }
        
  }
  
Simulation();

var n = 6;
var holdList;
var nodeList;
var nodeListM;
var fail = false;
var hold = false;
var temp = 0;
var countH = 0;
var countF = 0;
var countC = 0;
var arr = new Array();



   
