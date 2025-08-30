-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 18, 2023 at 06:20 PM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

-- Database: `coffee_shop`
-- -------------------------------------------------------

-- Table structure for table `admin`
CREATE TABLE `admin` (
  `AdminID` INT(11) NOT NULL,
  `username` VARCHAR(50) NOT NULL,
  `PhoneNo` VARCHAR(50) NOT NULL,
  `Password` VARCHAR(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping data for table admin
INSERT INTO `admin` (`AdminID`, `username`, `PhoneNo`, `Password`) VALUES
(1, 'Layla', '0199593729','adminpass1'),
(2, 'Syaf', '017362718', 'adminpass2');

-- Table structure for table customer
CREATE TABLE `customer` (
  `CustomerID` INT(11) NOT NULL,
  `username` VARCHAR(50) NOT NULL,
  `Password` VARCHAR(50) NOT NULL,
  `PhoneNo` VARCHAR(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping data for table customer
INSERT INTO `customer` (`CustomerID`, `username`, `Password`, `PhoneNo`) VALUES
(1, 'Teah','cust123', '0199590828'),
(2, 'haziq', 'cust123', '019626171');

--
-- Table structure for table `employee`
CREATE TABLE `employee` (
  `EmployeeID` INT(11) NOT NULL,
  `username` VARCHAR(50) NOT NULL,
  `Position` VARCHAR(50) NOT NULL,
  `SalaryPerMonth` DECIMAL(10,2),
  `Password` VARCHAR(50) NOT NULL,
  `PhoneNo` VARCHAR(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
--
-- Dumping data for table `employee`
INSERT INTO `employee` (`EmployeeID`, `username`, `Position`, `SalaryPerMonth`, `Password`, `PhoneNo`) VALUES
(1,'Ali', 'barista', 2500.00, 'emp123', '018261282'),
(2, 'Abu', 'cashier', 1500.00, 'emp123', '019726263');

-- Table structure for table `menu`
CREATE TABLE `menu` (
  `MenuID` INT(11) NOT NULL,
  `drink` VARCHAR(100) NOT NULL,
  `price` DECIMAL(10, 2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping data for table `menu`
INSERT INTO `menu` (`MenuID`, `drink`, `price`) VALUES
(101, 'Espresso', 3.50),
(102, 'Latte', 4.00),
(103, 'Cappuccino',  4.50),
(104, 'Americano', 3.00),
(105, 'Mocha',  4.75),
(106, 'Macchiato', 5.00),
(107, 'Flat White',  3.75),
(108, 'Cold Brew',  4.25),
(109, 'Iced Latte', 4.75),
(110, 'Chai Latte',  3.50);


-- Table structure for table `orders`
CREATE TABLE `orders` (
  `OrderID` INT(11) NOT NULL,
  `MenuID` INT(11) DEFAULT NULL,
  `OrderDate` DATE NOT NULL,
  `quantity` INT(11) NOT NULL,
  `total` DECIMAL(10, 2) NOT NULL,
  `CustomerID` INT(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping data for table `orders`
INSERT INTO `orders` (`OrderID`, `MenuID`, `OrderDate`, `quantity`, `CustomerID`) VALUES
(10, 101, '2024-06-20', 2, 1);


--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `PaymentID` INT(11) NOT NULL,
  `CustomerID` INT(11) NOT NULL,
  `total` DECIMAL(10, 2) NOT NULL,
  `paymentdate` DATE NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
--
-- Indexes for dumped tables
--
--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`AdminID`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`CustomerID`);

--
-- Indexes for table `employee`
--
ALTER TABLE `employee`
  ADD PRIMARY KEY (`EmployeeID`);

-- Indexes for table `menu`
--

ALTER TABLE `menu`
  ADD PRIMARY KEY (`MenuID`);

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`OrderID`),
  ADD KEY `MenuID` (`MenuID`),
  ADD KEY `CustomerID` (`CustomerID`);

-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`PaymentID`),
  ADD KEY `fk_payment_customer` (`CustomerID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `AdminID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `menu`
--
ALTER TABLE `menu`
  MODIFY `MenuID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=50;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `CustomerID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT for table `orders`
--
ALTER TABLE `orders`
  MODIFY `OrderID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `PaymentID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT for table `employee`
--
ALTER TABLE `employee`
  MODIFY `EmployeeID` INT(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- Constraints for dumped tables
--
--
-- Constraints for table `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `orders_ibfk_1` FOREIGN KEY (`MenuID`) REFERENCES `menu` (`MenuID`),
  ADD CONSTRAINT `orders_ibfk_2` FOREIGN KEY (`CustomerID`) REFERENCES `customer` (`CustomerID`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `fk_payment_customer` FOREIGN KEY (`CustomerID`) REFERENCES `customer` (`CustomerID`);


-- Commit the transaction
COMMIT;


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
