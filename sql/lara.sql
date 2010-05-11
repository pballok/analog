DROP TABLE IF EXISTS `logs`;

CREATE TABLE `logs` (
  `date`           TIMESTAMP           NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `severity`       INT(1)              NOT NULL DEFAULT 5,
  `message`        TEXT                         DEFAULT NULL,
  INDEX `in_logs_date` (`date` ASC)
) ENGINE=InnoDB;
