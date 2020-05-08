const addon = require("bindings")("addon.node");
const express = require("express");
const path = require('path');
const handlebars = require('express-handlebars');

const app = express();// create the express app

// Let the app handle json and urlencoded input
app.use(express.json());
app.use(express.urlencoded({
    extended: false
}));

// Initialize/set the Handlesbars instance/render engine
const handlebars_inst = handlebars.create({
    extname: '.handlebars',
    compilerOptions: {
        preventIndent: true
    },
    layoutsDir: path.join(__dirname, 'views', 'layouts'),
    partialsDir: path.join(__dirname, 'views', 'partials')
});
app.engine('handlebars', handlebars_inst.engine);
app.set('view engine', 'handlebars');
app.set('views', path.join(__dirname, 'views', 'pages'));


// Converts an operator to the C++ function associated with that operator
const funcMap = {
    "+": addon.add,
    "-": addon.minus,
    "*": addon.times,
    "/": addon.divide,
    "%": addon.mod,
};

// TODO - Have the user enter the calculation into a single textbox, parse that into the basic steps and then call the C++ addon functions
// TODO - Let the user store values inside of variables
// TODO - Let the user define functions that they can use
app.route('/')
    .get((req, res) => {
        res.status(200).render('page');
    })
    .post((req, res) => {
        // Acquire the new inputs
        let op1 = Number(req.body.operand1);
        let operation = req.body.operation;
        let op2 = Number(req.body.operand2);
        
        // Re-render the values the user provided
        res.locals.form = {
            "operand1": op1,
            "operation": operation,
            "operand2": op2
        };

        // Check if the operation is a valid/supported one - either give answer or give an alert
        if(!(operation in funcMap)){
            res.locals.alert = {"title": "Operation mismatch",'message': `Operation "${operation}" not supported`};
            res.render('page');
        } else {
            // The addons can throw errors, so catch them
            try {
                let answer = funcMap[operation](op1,op2);
                res.locals.answer = answer;
            } catch (e){
                res.locals.alert = {"title": "Operation Error", "message": e};
            }
            res.render('page');
        }
    });


app.listen(3000, () => {
    console.log('express app running at http://localhost:3000/')
});