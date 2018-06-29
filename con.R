library(bit64)
x <- "9007199254740993"
x <- as.integer64(x)
class(x)
typeof(x) <- 'integer64'
df <- data.frame(X = x)
class(df)
typeof(df)
class(df$X)

as(x, 'integer64')

library(dbplyr)
library(DBI)
library(bit64)
library(dplyr)
library(RClickhouse)
con <- DBI::dbConnect(RClickhouse::clickhouse(), host="db-imsm.wu.ac.at", user="daniel", password="vwl4ever123", db = "youtube")

RClickhouse::dbListTables(con)

test2 <- data.frame(2, stringsAsFactors = FALSE)

test2 <- data.frame(a = c(as.integer64(2), as.integer64(123123)), stringsAsFactors = FALSE)


DBI::dbWriteTable(con, name = "test_int", value = test2, overwrite = TRUE, field.types = "Int64")

test <- tbl(con, "test_int") %>%
  as.data.frame()
