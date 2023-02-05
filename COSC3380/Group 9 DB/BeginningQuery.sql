CREATE TABLE [user] (
userID INT NOT NULL PRIMARY KEY, 
username VARCHAR(30) NOT NULL, 
pword VARCHAR(20) NOT NULL, 
streetname VARCHAR(20) NOT NULL, 
city VARCHAR(20) NOT NULL, 
state VARCHAR(3) NOT NULL, 
country VARCHAR(20) NOT NULL, 
unitnum VARCHAR(5) NOT NULL
);

CREATE TABLE [payment] (
paymentID INT NOT NULL PRIMARY KEY,
paymentType VARCHAR(20) NOT NULL,
paymentFname VARCHAR(20) NOT NULL,
paymentLname VARCHAR(20) NOT NULL,
paymentDOB DATE NOT NULL,
paymentNum VARCHAR(16) NOT NULL,
paymentCVV VARCHAR(3) NOT NULL
);

CREATE TABLE [customer] (
customerID INT NOT NULL PRIMARY KEY,
fname VARCHAR(20) NOT NULL, 
lname VARCHAR(20) NOT NULL, 
address VARCHAR(40) NOT NULL, 
email VARCHAR(20) NOT NULL, 
userID INT NOT NULL,
CONSTRAINT FK_CustomerToUser FOREIGN KEY (userID) REFERENCES [user](userID)
);

CREATE TABLE [products] (
productID INT NOT NULL PRIMARY KEY, 
fullname VARCHAR(50) NOT NULL, 
productType VARCHAR(20) NOT NULL, 
prodDesc VARCHAR(125) NOT NULL, 
price DECIMAL(10,2) NOT NULL,
productQuantity INT DEFAULT 0,
discount DECIMAL(5,2),
CONSTRAINT disc_check CHECK (discount BETWEEN 0 AND 100)
);



CREATE TABLE [shoppingCart] (
customerID INT NOT NULL,
productID INT NOT NULL,
numItems INT NOT NULL,
CONSTRAINT FK_scToCustomer FOREIGN KEY (customerID) REFERENCES customer(customerID),
CONSTRAINT FK_scToProduct FOREIGN KEY (productID) REFERENCES products(productID)
);


CREATE TABLE [orders] (
orderID INT NOT NULL PRIMARY KEY,
customerID INT NOT NULL,
shippingAddress VARCHAR(50) NOT NULL,
billingAddress VARCHAR(50) NOT NULL,
orderAmount DECIMAL(10,2) NOT NULL,
shippingDate DATETIME NOT NULL,
paymentID INT NOT NULL,
CONSTRAINT FK_ordersToCustomer FOREIGN KEY (customerID) REFERENCES customer(customerID),
CONSTRAINT Fk_ordersToPayment FOREIGN KEY (paymentID) REFERENCES payment(paymentID)
);

CREATE TABLE [invoice] (
invoiceID INT NOT NULL PRIMARY KEY,
invoiceDate DATETIME NOT NULL,
amountBilled DECIMAL(10,2) NOT NULL,
tax DECIMAL(6,2) NOT NULL,
orderID INT NOT NULL,
CONSTRAINT FK_invoiceToOrders FOREIGN KEY (orderID) REFERENCES orders(orderID)
);

CREATE TABLE [supplier] (
supplierID INT NOT NULL PRIMARY KEY,
supplierName VARCHAR(20) NOT NULL,
address VARCHAR(40) NOT NULL,
email VARCHAR(40) NOT NULL,
phoneNum VARCHAR(10),
productID INT NOT NULL,
quantity INT NOT NULL,
CONSTRAINT FK_supplierToProduct FOREIGN KEY (productID) REFERENCES products(productID)
);