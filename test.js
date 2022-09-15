function lore(current, pre) {
  if (
    ((current == "+" || current == "-") &&
      (pre == "*" || pre == "/" || pre == "^" || pre == "+" || pre == "-")) ||
    current == pre
  )
    // + +  |  * *  |  ^ ^  |  + *  | * +  | ^ *  | * ^  | + -
    return true;
  else if (
    ((current == "*" || current == "/") && (pre == "*" || pre == "/")) ||
    (current != "^" && pre == "^")
  )
    return true;
  return false;
}
function isOperator(o) {
  if (o == "+" || o == "-" || o == "/" || o == "*" || o == "^") return true;
  return false;
}
/* calc function */
let nums = document.querySelectorAll(".btns_num");
let show = document.getElementById("show");
function calc(eq) {
  eq = eq.split(" ");
  let l = eq.length;
  let stack = [];
  for (let i = 0; i < eq.length; i++) {
    if (isOperator(eq[i])) {
      if (!stack.length) {
        stack.push(eq[i]);
        eq.splice(i, 1);
      } else {
        if (lore(eq[i], stack[stack.length - 1]))
          [eq[i], stack[stack.length - 1]] = [stack[stack.length - 1], eq[i]];
        else {
          stack.push(eq[i]);
          eq.splice(i, 1);
        }
      }
    }
  }
  while (stack.length) eq.push(stack.pop());
  for (let i = 0; i < l; i++) {
    if (!isOperator(eq[i])) stack.push(eq[i]);
    else {
      let n2 = stack.pop(),
        n1 = stack.pop();
      stack.push(calcExp(+n1, +n2, eq[i]));
    }
  }
  return String(stack.pop());
}
function calcExp(n1, n2, operator) {
  switch (operator) {
    case "+":
      return n1 + n2;
    case "-":
      return n1 - n2;
    case "*":
      return n1 * n2;
    case "/":
      return n1 / n2;
    case "^":
      return Math.pow(n1, n2);
  }
}

nums.forEach((e) => {
  e.onclick = function () {
    let eVal = e.innerHTML;
    if (Number.isInteger(+eVal) || eVal == ".") show.innerHTML += eVal;
    else if (eVal === "AC") show.innerHTML = "";
    else if (eVal === "DEL") {
      if (show.innerHTML[show.innerHTML.length - 1] == " ")
        show.innerHTML = show.innerHTML.slice(0, -3);
      else show.innerHTML = show.innerHTML.slice(0, -1);
    } else if (eVal === "=") show.innerHTML = calc(show.innerHTML);
    else show.innerHTML += ` ${eVal} `;
  };
});
