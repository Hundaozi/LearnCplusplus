//表示非原始类型，一个对象

declare function create(o:object | null) :void;

create({prop:0});
create(null);
// create(42); //error

// create("string");//error