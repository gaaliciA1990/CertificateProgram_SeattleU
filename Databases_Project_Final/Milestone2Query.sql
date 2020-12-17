/*
This shows the inventory for our product_bom where the product and their corresponding materials 
inventory are both less than 100. This will be our indication to put in an order for more materials
to keep up our inventory.
*/
SELECT	mi.product_item_id AS material_id,
		pbom.product_description AS material_description, -- what the product is that we are targeting
		mi.quantity
FROM manufacturer_inventory mi
	INNER JOIN product_bom pbom
		ON mi.product_item_id = pbom.product_item_id
WHERE mi.quantity <= 100
	AND pbom.quantity <=100;

/*
This query shows the products with lowest ratings (1-2.5) and with highest ratings (5)
for the last 30 days. This will aide in determining which products are our most popular
so we can invest in those materials, and which are our least.
*/
SELECT	cr.product_id,
		p.model_name,
		ROUND (AVG(cr.rating_score),2) AS average_rating
FROM customer_ratings cr
	RIGHT JOIN products p
		ON cr.product_id = p.product_id
WHERE cr.review_date between (curdate() - interval 30 day) AND curdate()
GROUP BY 1
HAVING average_rating Between (1) AND  (2.9)
	OR average_rating = 5
ORDER BY average_rating desc; 

/*
This query will pull the ratings per customer per product for feedback (VOC).
Customer data is pulled to initiate a contact with the cutomer to dive into how we can 
improve our products further as a part of our company customer outreach program
*/
SELECT cr.product_id, 
		cr.rating_score,
        p.model_name,
        c.customer_name,
        c.phone, 
        c.email
FROM customer_ratings cr
	JOIN customers c
		ON cr.customer_id = c.customer_id
	RIGHT JOIN products p
		ON cr.product_id = p.product_id
WHERE cr.rating_score <= 3;

/*
This query will pull the payment methods by week to determine which method is most commonly used.
*/
with totals as (
select yearweek(co.order_date_local, 4) as order_week
	 , sum(case when pm.payment_method = 'Cash' then 1 else 0 end) as cash_count
     , sum(case when pm.payment_method = 'Check' then 1 else 0 end) as check_count
     , sum(case when pm.payment_method = 'Apple Pay' then 1 else 0 end) as apple_count
     , sum(case when pm.payment_method = 'Discover' then 1 else 0 end) as discover_count
     , sum(case when pm.payment_method = 'American Express' then 1 else 0 end) as amex_count
     , sum(case when pm.payment_method = 'Google Pay' then 1 else 0 end) as google_count
     , sum(case when pm.payment_method = 'Master Card' then 1 else 0 end) as master_count
     , sum(case when pm.payment_method = 'Paypal' then 1 else 0 end) as paypal_count
     , sum(case when pm.payment_method = 'Venmo' then 1 else 0 end) as venmo_count
     , sum(case when pm.payment_method = 'Visa' then 1 else 0 end) as visa_count
     , count(*) as total_count
from customer_orders co
	 inner join payment_methods pm on co.payment_id = pm.payment_id
group by 1
)
select order_week
     , cash_count / total_count as cash_mix
     , check_count / total_count as check_mix
     , apple_count / total_count as apple_mix
     , discover_count / total_count as discover_mix
     , amex_count / total_count as amex_mix
     , google_count / total_count as google_mix
     , master_count / total_count as master_mix
     , paypal_count / total_count as paypal_mix
     , venmo_count / total_count as venmo_mix
     , visa_count / total_count as visa_mix
from totals
order by 1;

/*
This query will show which backpack sizes are our most popular.
*/
select yearweek(co.order_date_local) as order_week
	 , case when p.capacity_liters < 10.0 then '01 - small'
			when p.capacity_liters < 40 then '02 - medium'
            when p.capacity_liters < 75 then '03 - large'
            else '04 - x-large' end as size
	 , sum(cod.quantity) as qty_sold
from customer_orders co
	 inner join customer_order_details cod on co.order_id = cod.order_id
     inner join products p on cod.product_id = p.product_id
group by 1,2
order by 1,2;

/*
This query will pull the average items per box (equating to shipment) by week
*/
select yearweek(co.order_date_local) as order_week
	 , avg(cast(cod.quantity as double) / co.box_count) as avg_units_per_box
from customer_orders co
	 inner join customer_order_details cod on co.order_id = cod.order_id
group by 1
order by 1
;

/*
This query will show our most expensive vendor we are purchasing products. 
The manufacture costs are treated as CNY and coverted to USD, otherwise,
we're not doing too good
*/
SELECT
model_name,
cod.product_id,
vendor_id,
vendor_name,
cod.product_id,
ROUND(pb.quantity * pod.purchase_price/7, 2)  as manufacture_cost
from customer_order_details as cod, product_bom as pb, products as p, purchase_order_details as pod, vendors as v
where
(cod.product_id = pb.product_id
AND cod.product_id = p.product_id
AND pb.product_item_id = pod.product_item_id
AND pb.product_item_id = v.product_item_id)
-- rank by cost
order by pb.quantity * pod.purchase_price/7 desc;

/*
Most profitable products we sell. 
*/
SELECT 
model_name,
cod.order_id, 
cod.product_id, 
cod.quantity,
cod.purchase_price,
cod.quantity * cod.purchase_price  as total_sale,
ROUND(pb.quantity * pod.purchase_price/7,2)  as manufacture_cost,
ROUND(cod.quantity * cod.purchase_price - pb.quantity * pod.purchase_price /7,2) as profit
from customer_order_details as cod, product_bom as pb, products as p, purchase_order_details as pod
where 
(cod.product_id = pb.product_id 
AND cod.product_id = p.product_id 
AND pb.product_item_id = pod.product_item_id 
AND (cod.quantity * cod.purchase_price) - (pb.quantity * pod.purchase_price /7) > 0)
order by (cod.quantity * cod.purchase_price) - (pb.quantity * pod.purchase_price /7) desc;


/* 
This query that gets our customer data across the country (EastCoast, WestCoast, MidWest) to see
see how our general customers are spread out. This also helps us determine where to set up new
offices or where to prioritize our growth. 
*/
select
count(EastCoast) as EastCoast,
count(WestCoast) as WestCoast,
count(MidWest) as MidWest,
count(TheSouth) as TheSouth
from(
select
case when state in ('Rh','Ma','Co','No','So','Vi','De') then 1 end EastCoast,
case when state in ('Or', 'Wa','Ca','Ha','Id','Wy','Ut','Al') then 1 end WestCoast,
case when state in ('Pe', 'II','In','Ka','Wi', 'Ne','Ar','Io') then 1 end MidWest,
case when state in ('Ge', 'Fl','Ke','Ok','Mi','Ma','Te') then 1 end TheSouth
from customers
) customers;

/*
A query to get number of expected arrivals per delivery day, and susequently find our busiest day
which is Sunday. This will enable us to make sure there is adequte support for our customers on that day incase they
have trouble with the shipment 
*/
select  DAYNAME(arrival_date_local) as WeekDay, COUNT(*) as No_of_deliveries
from purchase_orders
group by DAYNAME(arrival_date_local)
order by COUNT(*) DESC;

/*
STORED PROCEDURE
This query is similar to the above query but is state wide. Tennessee seems to be the state with the most
customers followed by california. This query has been saved as a procedure 
*/
DELIMITER //
DROP PROCEDURE customerbystate;
CREATE PROCEDURE customerbystate
()
BEGIN
select state, count(*) as total from customers group by state order by total desc;
END //
DELIMITER ;
call customerbystate();