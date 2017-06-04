class Queue {
  constructor() {
    this.items = []
  }
}

Queue.prototype.enqueue = function enqueue(obj) {
    this.items.push(obj);
};

Queue.prototype.dequeue = function dequeue() {
    return this.items.shift();
};

Queue.prototype.isEmpty = function isEmpty() {
    return this.items.length === 0;
};

const myQueue = new Queue()

console.log(myQueue.isEmpty())
myQueue.enqueue(44)
myQueue.enqueue(77)
myQueue.enqueue(4)

console.log(myQueue.isEmpty())
console.log(myQueue)

myQueue.dequeue()
console.log(myQueue)
myQueue.enqueue(100)
console.log(myQueue)
