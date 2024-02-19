class Student {
    fullName: string;
    constructor(public firstName, public middleInitial, public lastName) {
        this.fullName = firstName + " " + middleInitial + " " + lastName;
    }
}

interface Person {
    firstName: string;
    lastName: string;
}
//类型注解
function greeter(person:Person){
    return "hello, " + person.firstName+ " "+person.lastName;
}

let user = new Student("Li","h","yonghua");//实例化一个类
document.body.innerHTML=greeter(user);