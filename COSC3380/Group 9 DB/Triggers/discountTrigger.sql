/****** Object:  Trigger [dbo].[orders_deal_notice_001]    Script Date: 11/16/2022 9:19:38 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- ==============================================
-- Create dml trigger template Azure SQL Database 
-- ==============================================
-- Drop the dml trigger if it already exists
/*
IF EXISTS(
  SELECT *
    FROM sys.triggers
   WHERE name = N'<Trigger_Name, sysname, Trigger_Name>'
     AND parent_class_desc = N'OBJECT_OR_COLUMN'
)
	DROP TRIGGER <Schema_Name, sysname, Schema_Name>.<Trigger_Name, sysname, Trigger_Name>
GO

CREATE TRIGGER <Schema_Name, sysname, Schema_Name>.<Trigger_Name, sysname, Trigger_Name> 
   ON  <Schema_Name, sysname, Schema_Name>.<Table_Name, sysname, Table_Name> 
   AFTER <Data_Modification_Statements, , INSERT,DELETE,UPDATE>
AS 
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for trigger here

END
GO */

ALTER TRIGGER [dbo].[orders_deal_notice_001] ON [dbo].[orders] 
AFTER INSERT
--FOR EACH ROW
AS
BEGIN
SET NOCOUNT ON;
--so goal is to notify the user that with their current cart that they are eligible for a deal (which is to give them a free item)
--we declare the variables that will be used as parameters 
declare @orders_id int; 
--declare @product_cost int;
declare @product_id int;
declare @cartTotal int; 

-- we make the new variables equal the incoming variables 
--these are calling from the orders table
select @cartTotal = orders.orderAmount from orders;
select @orders_id = orders.orderID from orders; 

--these call from the product table
select @product_id = products.productID from products where productID = 10; 
-- select @product_cost = orders.costPerProduct from orders where  orders.idorders  = @product_id; -- the product id for socks


if (@cartTotal <= 5.00) 
    INSERT INTO Deals(idDeals, ProductId,orderid, status )
    VALUES ( 101, @product_id,@orders_id, 'qualified' );
else 
   INSERT INTO Deals(ProductId, orderid, status )
    VALUES ( @product_id,@orders_id, 'not qualified' );
END 
