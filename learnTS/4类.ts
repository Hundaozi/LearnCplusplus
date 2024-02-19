// class Greeter{
//     greeting:string;
//     constructor(message:string){
//         this.greeting=message;
//     }
//     greet(){
//         return "你好, "+this.greeting;
//     }
// }
// let greeter=new Greeter("世界");

//继承

// class Animal {
//     move(distanceInMeters: number = 0) {
//         console.log(`Animal moved ${distanceInMeters}m.`);
//     }
// }

// class Dog extends Animal {
//     bark() {
//         console.log('Woof! Woof!');
//     }
// }

// const dog = new Dog();
// dog.bark();
// dog.move(10);
// dog.bark();

// class Animal{
//     name:string;
//     constructor(theName:string){
//         this.name=theName;
//     }
//     move(distanceInMeters:number=0){
//         console.log(`${this.name} moved ${distanceInMeters}m.`);
//     }
// }

// class Snake extends Animal{
//     constructor(name:string){
//         super(name);//继承父类的属性
//     }
//     move(distanceInMeters=5){
//         console.log("蛇正在移动...");
//         super.move(distanceInMeters);
//     }
// }
// class Horse extends Animal{
//     constructor(name:string){
//         super(name);
        
//     }
//     move(distanceInMeters=45){
//         console.log("马来喽。。。");
//         super.move(distanceInMeters);
//     }
// }

// let sam=new Snake("这是Python");
// let tom:Animal=new Horse("Tom无所不能");

// sam.move();
// tom.move(34);

// class Animal{
//     public name:string;
//     public constructor(theName:string)
//     {
//         this.name=theName;
//     }
//     public move(distanceInMeters:number){
//         console.log(`${this.name} moved ${distanceInMeters}m.`);
//     }
// }
// let hahah=new Animal("卢本伟");

// hahah.move(10);

// //public:公有
// //protected:保护
// //private:私有
// //C++里已经学过了
//可以使用 readonly关键字将属性设置为只读的。 
//只读属性必须在声明时或构造函数里被初始化。
// class Octopus {
//     readonly name: string;
//     readonly numberOfLegs: number = 8;
//     constructor (theName: string) {
//         this.name = theName;
//     }
// }
// let dad = new Octopus("Man with the 8 strong legs");
// console.log(dad.name);

//TypeScript支持通过getters/setters来截取对对象成员的访问。
// class Employee {
//     fullName: string;
// }

// let employee = new Employee();
// employee.fullName = "Bob Smith";
// if (employee.fullName) {
//     console.log(employee.fullName);
// }

// let passcode = "secret passcode";

// class Employee {
//     private _fullName: string;

//     get fullName(): string {
//         return this._fullName;
//     }

//     set fullName(newName: string) {
//         if (passcode && passcode == "secret passcode") {
//             this._fullName = newName;
//         }
//         else {
//             console.log("Error: Unauthorized update of employee!");
//         }
//     }
// }

// let employee = new Employee();
// employee.fullName = "Bob Smith";
// if (employee.fullName) {
//     alert(employee.fullName);
// }

//static 静态属性
// class Grid {
//     static origin = {x: 0, y: 0};
//     calculateDistanceFromOrigin(point: {x: number; y: number;}) {
//         let xDist = (point.x - Grid.origin.x);
//         let yDist = (point.y - Grid.origin.y);
//         return Math.sqrt(xDist * xDist + yDist * yDist) / this.scale;
//     }
//     constructor (public scale: number) { }
// }

// let grid1 = new Grid(1.0);  // 1x scale
// let grid2 = new Grid(5.0);  // 5x scale

// console.log(grid1.calculateDistanceFromOrigin({x: 10, y: 10}));
// console.log(grid2.calculateDistanceFromOrigin({x: 10, y: 10}));

//抽象类做为其它派生类的基类使用。
// 它们一般不会直接被实例化。 不同于接口，抽象类可以包含成员的实现细节。 
//abstract关键字是用于定义抽象类和在抽象类内部定义抽象方法。
// abstract class Animal{
//     abstract makeSound():void;
//     //对于属性，应该对应C++里面的虚函数，被子类所实现
//     move(): void {
//         console.log('鸡汤来咯...');
//     }
// }
// class Greeter {
//     greeting: string;
//     constructor(message: string) {
//         this.greeting = message;
//     }
//     greet() {
//         return "Hello, " + this.greeting;
//     }
// }

// let greeter: Greeter;//类型匹配,声明了实例的类型
// greeter = new Greeter("world");
// console.log(greeter.greet());

//把类当做接口使用
//老概念了
class Point {
    x: number;
    y: number;
}

interface Point3d extends Point {
    z: number;
}

let point3d: Point3d = {x: 1, y: 2, z: 3};
