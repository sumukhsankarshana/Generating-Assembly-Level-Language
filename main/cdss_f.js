// No libraries needed

class bin_tree {
  constructor(val, l) {
    this.right = null;
    this.left = null;
    this.data = val;
    this.label = l;
  }
}

 

  class dag {
    constructor() {
      this.R = [];
      this.top = -1;
      this.op = "";
    }
    
    initializestack(root) {
      this.top = root.label - 1;
      let temp = this.top;
      for (let i = 0; i <= this.top; i++) {
        this.R[i] = temp;
        temp--;
      }
      
    }
  
    insertnode(tree, val) {
      if (!tree) {
          const temp = new bin_tree(val, -1);
          tree = temp;
          
      }
      return tree;
  }

  insert(tree, val) {
      var l, r;
      let numofchildren;
      tree = this.insertnode(tree, val);
      console.log(`\nEnter number of children of ${val}:`);
      numofchildren = Number(prompt(`\nEnter number of children of ${val}:`));
      if (numofchildren === 2) {
          console.log(`\nEnter Left Child of ${val}:`);
          l = prompt(`\nEnter Left Child of ${val}:`);
          tree.left = this.insertnode(tree.left,l);
          console.log(`\nEnter Right Child of ${val}:`);
          r = prompt(`\nEnter Right Child of ${val}:`);
          tree.right = this.insertnode(tree.right, r);
          this.insert(tree.left, l);
          this.insert(tree.right, r);
      }
      return tree;
  }

      findleafnodelabel(tree, val) {
        if (tree.left != null && tree.right != null) {
            this.findleafnodelabel(tree.left, 1);
            this.findleafnodelabel(tree.right, 0);
        } else {
            tree.label = val;
        }
    }
    
    findinteriornodelabel(tree) {
        if (tree.left.label == -1) {
            this.findinteriornodelabel(tree.left);
        } else if (tree.right.label == -1) {
            this.findinteriornodelabel(tree.right);
        } else {
            if (tree.left != null && tree.right != null) {
                if (tree.left.label == tree.right.label) {
                    tree.label = tree.left.label + 1;
                } else {
                    if (tree.left.label > tree.right.label) {
                        tree.label = tree.left.label;
                    } else {
                        tree.label = tree.right.label;
                    }
                }
            }
        }
    }
print_inorder(tree) {
  if (tree) {
    this.print_inorder(tree.left);
    console.log(tree.data + " with Label " + tree.label);
    
    document.getElementById("result1").innerHTML+=tree.data + " with Label " + tree.label+"<br>";
    this.print_inorder(tree.right);
  }
}

swap() {
  let temp;
  temp = this.R[0];
  this.R[0] = this.R[1];
  this.R[1] = temp;
}

pop() {
  let temp = this.R[this.top];
  this.top--;
  return temp;
}

push(temp) {
  this.top++;
  this.R[top] = temp;
}
nameofoperation(temp) {
  switch (temp) {
    case '+':
      this.op = "ADD";
      break;
    case '-':
      this.op = "SUB";
      break;
    case '*':
      this.op = "MUL";
      break;
    case '/':
      this.op = "DIV";
      break;
  }
}
gencode(tree) {
  
  if (tree.left != null && tree.right != null) {
    if (tree.left.label == 1 && tree.right.label == 0 && tree.left.left == null && tree.left.right == null && tree.right.left == null && tree.right.right == null) {
      
      console.log("MOV " + tree.left.data + ",R[" + this.R[this.top] + "]" + "\n");
      
      document.getElementById("result2").innerHTML+="MOV " + tree.left.data + ",R[" + this.R[this.top] + "]"+ "<br>";
      this.nameofoperation(tree.data);
      console.log(`${this.op} ${tree.right.data}, R[${this.R[this.top]}]`);
      
      document.getElementById("result2").innerHTML+=`${this.op} ${tree.right.data}, R[${this.R[this.top]}]`+"<br>";
    } else if (tree.left.label >= 1 && tree.right.label == 0) {
      this.gencode(tree.left);
      this.nameofoperation(tree.data);
      this.console.log(`${this.op} ${tree.right.data}, R[${this.R[this.top]}]`);
      
      document.getElementById("result2").innerHTML+=`${this.op} ${tree.right.data}, R[${this.R[this.top]}]`+"<br>";

    } else if (tree.left.label < tree.right.label) {
      let temp;
      this.swap();
      this.gencode(tree.right);
      temp = this.pop();
      this.gencode(tree.left);
      this.push(temp);
      this.swap();
      this.nameofoperation(tree.data);
      console.log(`${this.op} R[${this.R[this.top - 1]}], R[${this.R[this.top]}]`);
    
      document.getElementById("result2").innerHTML+=`${this.op} R[${this.R[this.top - 1]}], R[${this.R[this.top]}]`+"<br>";
    } else if (tree.left.label >= tree.right.label) {
      let temp;
      this.gencode(tree.left);
      temp = this.pop();
      this.gencode(tree.right);
      this.push(temp);
      this.nameofoperation(tree.data);
      console.log(`${this.op} R[${this.R[this.top - 1]}], R[${this.R[this.top]}]`);
      
      document.getElementById("result2").innerHTML+=`${this.op} R[${this.R[this.top - 1]}], R[${this.R[this.top]}]`+"<br>";
    }
  } else if (tree.left == null && tree.right == null && tree.label == 1) {
    console.log(`MOV ${tree.data}, R[${this.R[this.top]}]`);
   
    document.getElementById("result2").innerHTML+=`MOV ${tree.data}, R[${this.R[this.top]}]`+"<br>";

  }
}

deltree(tree) {
  if (tree) {
    this.deltree(tree.left);
    this.deltree(tree.right);
    tree = null;
  }
}
}
var root;
root = null;
let tmp;
let val;
let i, temp;
const d = new dag();
function inputfuntion() {
    let cdss =document.getElementById("root");
    if(cdss.value==""){
      alert("Please Enter Root Node");
      return;
    }
    val = cdss.value;
    root=d.insert(root, val);
    d.findleafnodelabel(root, 1);
    while (root.label === -1) {
      d.findinteriornodelabel(root);
    }
    d.initializestack(root);
    console.log("\nInorder Display:\n");
    document.getElementById("result1").innerHTML+="";
    d.print_inorder(root);
    console.log("\nAssembly Code:\n");
    document.getElementById("result2").innerHTML+="";
    d.gencode(root);
    d.deltree(root);
}


