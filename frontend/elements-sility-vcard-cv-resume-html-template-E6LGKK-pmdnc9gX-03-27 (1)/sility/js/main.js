var csvStringState = [`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
1,0,0,0,0,0,0,0,0,0,0,0
,,,,1,0,0,0,0,,,
,,,,2,0,0,0,0,,,
,,,,3,0,0,0,0,,,
,,,,4,0,0,0,0,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,0,1,0,0,0,0,0,0,0,0,0
1,1,0,0,1,0,0,0,0,,,
,,,,2,0,0,0,0,,,
,,,,3,0,0,0,0,,,
,,,,4,0,0,0,0,,,`,
`matrizCreada ,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,0,0,1,0,0,0,0,0,0,0,0
0,1,0,1,1,0,0,0,0,,,
1,2,0,0,2,0,0,0,0,,,
,,,,3,0,0,0,0,,,
,,,,4,0,0,0,0,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,,0,0,0,1,0,0,0,0,0,0
0,,0,0,1,0,0,0,0,,,
0,2,0,0,2,0,0,0,0,,,
1,3,0,0,3,0,0,0,0,,,
,,,,4,0,0,0,0,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,,0,0,0,1,0,0,0,0,0,0
0,,0,0,1,0,0,0,0,,,
0,2,1,0,2,0,0,0,0,,,
0,3,0,0,3,0,0,0,0,,,
1,4,0,0,4,0,0,0,0,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,,0,0,0,0,1,0,0,0,0,0
0,,0,0,1,0,0,0,0,,,
0,2,0,1,2,0,0,0,0,,,
0,3,0,0,3,0,0,0,0,,,
0,4,0,1,4,0,0,0,0,,,
1,5,0,,,,,,,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,,0,0,0,0,0,0,0,0,1,0
0,,0,0,1,1,0,0,0,,,
0,,0,0,2,0,0,0,0,,,
0,3,1,0,3,0,0,0,0,,,
0,,0,0,4,0,0,0,0,,,
0,5,0,,,,,,,,,
1,6,0,,,,,,,,,`,
`matrizCreada,idMatriz,hold,mult,nProces,working,rc,rb,finish,nFinish,nFail,nHold
0,,0,0,0,0,0,0,0,1,1,0
0,,0,0,1,0,0,0,1,,,
0,,0,0,2,0,0,0,0,,,
0,3,0,1,3,0,0,0,0,,,
0,,0,0,4,0,0,0,0,,,
0,5,0,0,,,,,,,,
0,6,0,1,,,,,,,,`]; 

// const csvString=`idMatriz,hold,mult,nproces,working,rc,rb,finish,nfinish,nfail
// 0,1,0,0,0,0,0,0,0,0
// ,,,1,0,0,0,0,0,0
// ,,,2,0,0,0,0,0,0
// ,,,3,0,0,0,0,0,0
// ,,,4,0,0,0,0,0,0
// ,,,5,0,0,0,0,0,0`

// const csvString2=`idMatriz,hold,mult,nproces,working,rc,rb,finish,nfinish,nfail
// 0,1,0,0,0,0,0,0,0,0
// 1,0,0,1,0,0,0,0,0,0
// ,,,2,0,0,0,0,0,0
// ,,,3,0,0,0,0,0,0
// ,,,4,0,0,0,0,0,0
// ,,,5,0,0,0,0,0,0`

// d3.csv("./simul.csv").then(function(data) {
//     console.log(data[0]);
//   });


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

    function writeNum(clase,n)
    {
        $( clase ).replaceWith( "<h2>"+ n + "</h2>" );
    }

    function resolveAfter1Seconds() {
        return new Promise(resolve => {
          setTimeout(() => {
            resolve('resolved');
          }, 1000);
        });
      }

async function Simulation() {
    const stateArrayInit=await csv(csvConfig).fromString(csvStringState[0]);
    var nProces = stateArrayInit.length;
    console.log(nProces);
    createPro(nProces);
    for (let index = 0; index < csvStringState.length; index++) {
        
            console.log("State it: " + index);
            const stateArray=await csv(csvConfig).fromString(csvStringState[index]);
            console.log(stateArray);

            if(stateArray.length != 0 )
            {
            nodeList = document.querySelectorAll("div.bola_p1");
            for (let k = 0; k < stateArrayInit.length; k++) {
                    if (fail == true) {
                    var num = countF;
                    writeNum(".numF",num);
                    fail = false;
                    }
                    if (stateArray[k].working == 0 && stateArray[k].rc == 0 && stateArray[k].rb == 0) {
                        nodeList[k].style.backgroundColor = "red";
                    }else if(stateArray[k].working == 1){
                        nodeList[k].style.backgroundColor = "green";
                    }else if(stateArray[k].rc == 1 && stateArray[k].rb == 0){
                        nodeList[k].style.backgroundColor = "yellow";
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        await resolveAfter1Seconds();
                        fail = true;
                        ++countF; 
                    }
                    
                    if (stateArray[k].finish == 1) {
                         ++countC;
                        var num = countC;
                        writeNum(".numC",num);
                                            
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
                    }else if (stateArray[k].mult == "1") {
                        nodeListM[k].style.backgroundColor = "blue";
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

  anime({
    targets: 'div.bola_p1',
    translateY: [
        {value:250, duration:500},
        {value: 0, duration:500, delay: 2000}
]
}); 

var n = 6;
var holdList;
var nodeList;
var nodeListM;
var fail = false;
var countF = 0;
var countC = 0;
var arr = new Array();


   
