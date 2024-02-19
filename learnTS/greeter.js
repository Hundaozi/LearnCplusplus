var Student = /** @class */ (function () {
    function Student(firstName, middleInitial, lastName) {
        this.firstName = firstName;
        this.middleInitial = middleInitial;
        this.lastName = lastName;
        this.fullName = firstName + " " + middleInitial + " " + lastName;
    }
    return Student;
}());
//类型注解
function greeter(person) {
    return "hello, " + person.firstName + " " + person.lastName;
}
var user = new Student("Li", "h", "yonghua"); //实例化一个类
document.body.innerHTML = greeter(user);
