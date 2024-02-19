//:string将person参数注解为string型
function greeter(person:string){
    return "hello, " + person
}

let myuser = "yonghua li";
document.body.innerHTML=greeter(myuser);