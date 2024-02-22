// function add(x,y):number {
//     return x+y;
// }
// let myadd=function(x,y):number{
//     return x+y;//匿名函数
// }

// //完整的函数
// let myadd2:(baseValue:number,increment:number)=>number=
//     function(x:number,y:number):number{
//         return x+y;//一句话总结，带类型注解的lambda匿名函数
//     }

//     //传递给一个函数的参数个数必须与函数期望的参数个数一致。

// function buildName(firstName:string,lastName?:string){
//     if(lastName)
//         return firstName+" " + lastName;
//     else   
//         return firstName;
// }
// let result1=buildName("Bob");
// let result2 = buildName("Bob", "Adams", "Sr.");  // error, too many parameters
// let result3 = buildName("Bob", "Adams");  // ah, just right

//剩余参数
// function buildName(firstName: string, ...restOfName: string[]) {
//     return firstName + " " + restOfName.join(" ");
//   }
  
//   let employeeName = buildName("Joseph", "Samuel", "Lucas", "MacKinzie");
//使用...省略，类似于C++模版参数的语法糖

// interface Card {
//     suit: string;
//     card: number;
// }
// interface Deck {
//     suits: string[];
//     cards: number[];
//     createCardPicker(this: Deck): () => Card;
// }
// let deck: Deck = {
//     suits: ["hearts", "spades", "clubs", "diamonds"],
//     cards: Array(52),
//     // NOTE: The function now explicitly specifies that its callee must be of type Deck
//     createCardPicker: function(this: Deck) {
//         return () => {
//             //对this进行类型注解，这里的this指向Deck接口
//             let pickedCard = Math.floor(Math.random() * 52);
//             let pickedSuit = Math.floor(pickedCard / 13);

//             return {suit: this.suits[pickedSuit], card: pickedCard % 13};
//         }
//     }
// }

// let cardPicker = deck.createCardPicker();
// let pickedCard = cardPicker();

// alert("card: " + pickedCard.card + " of " + pickedCard.suit);

//箭头函数不会捕获this