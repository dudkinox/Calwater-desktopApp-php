-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 12, 2021 at 07:35 AM
-- Server version: 10.4.19-MariaDB
-- PHP Version: 8.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `calwater`
--

-- --------------------------------------------------------

--
-- Table structure for table `ca`
--

CREATE TABLE `ca` (
  `ca` decimal(50,9) NOT NULL,
  `model` decimal(50,9) NOT NULL,
  `lab` decimal(50,9) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `ca`
--

INSERT INTO `ca` (`ca`, `model`, `lab`, `No`) VALUES
('0.349354898', '61.454321400', '61.500436200', 1),
('0.629833021', '92.327222550', '92.396504200', 2);

-- --------------------------------------------------------

--
-- Table structure for table `fe`
--

CREATE TABLE `fe` (
  `fe` decimal(50,9) NOT NULL,
  `model` decimal(50,9) NOT NULL,
  `lab` decimal(50,9) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `fe`
--

INSERT INTO `fe` (`fe`, `model`, `lab`, `No`) VALUES
('1.238195409', '85.747508500', '75.302092000', 1),
('2.221446155', '128.199657600', '112.582891100', 2);

-- --------------------------------------------------------

--
-- Table structure for table `info`
--

CREATE TABLE `info` (
  `ID` int(100) NOT NULL,
  `Batch_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Meet_MOI_Spec` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Sump_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Treatment_Date` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Ca` int(10) NOT NULL,
  `Fe` int(10) NOT NULL,
  `Na` int(10) NOT NULL,
  `TDS` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `info`
--

INSERT INTO `info` (`ID`, `Batch_No`, `Meet_MOI_Spec`, `Sump_No`, `Treatment_Date`, `Ca`, `Fe`, `Na`, `TDS`) VALUES
(1, '2021001', 'YES', 'S2', '10/12/2021', 1, 1, 1, 1),
(2, '2021002', 'YES', 'S2', '10/12/2021', 2, 2, 2, 2);

-- --------------------------------------------------------

--
-- Table structure for table `input`
--

CREATE TABLE `input` (
  `Vlume` decimal(50,9) NOT NULL,
  `Total_Cr` decimal(50,9) NOT NULL,
  `Cu` decimal(50,9) NOT NULL,
  `Mn` decimal(50,9) NOT NULL,
  `Ni` decimal(50,9) NOT NULL,
  `Pb` decimal(50,9) NOT NULL,
  `Zn` decimal(50,9) NOT NULL,
  `No` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `input`
--

INSERT INTO `input` (`Vlume`, `Total_Cr`, `Cu`, `Mn`, `Ni`, `Pb`, `Zn`, `No`) VALUES
('12.000000000', '12.000000000', '12.000000000', '1.000000000', '212.000000000', '12.000000000', '12.000000000', 1),
('10.000000000', '110.300000000', '54.430000000', '2.239000000', '44.940000000', '0.001000000', '201.200000000', 2);

-- --------------------------------------------------------

--
-- Table structure for table `na`
--

CREATE TABLE `na` (
  `na` decimal(50,9) NOT NULL,
  `model` decimal(50,9) NOT NULL,
  `lab` decimal(50,9) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `na`
--

INSERT INTO `na` (`na`, `model`, `lab`, `No`) VALUES
('13.330000000', '159.960000000', '132.000000000', 1),
('13.330000000', '133.300000000', '110.000000000', 2);

-- --------------------------------------------------------

--
-- Table structure for table `tds`
--

CREATE TABLE `tds` (
  `tds` decimal(50,9) NOT NULL,
  `model` decimal(50,9) NOT NULL,
  `lab` decimal(50,9) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `tds`
--

INSERT INTO `tds` (`tds`, `model`, `lab`, `No`) VALUES
('0.000000000', '8358.350000000', '7760.570000000', 1),
('0.000000000', '8413.210000000', '8055.640000000', 2);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ca`
--
ALTER TABLE `ca`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `fe`
--
ALTER TABLE `fe`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `info`
--
ALTER TABLE `info`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `input`
--
ALTER TABLE `input`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `na`
--
ALTER TABLE `na`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `tds`
--
ALTER TABLE `tds`
  ADD PRIMARY KEY (`No`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `info`
--
ALTER TABLE `info`
  MODIFY `ID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
