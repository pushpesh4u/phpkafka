/**
 *  Copyright 2015 Elias Van Ootegem.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Special thanks to Patrick Reilly and Aleksandar Babic for their work
 * On which this extension was actually built.
 */
#ifndef PHP_KAFKA_H
#define	PHP_KAFKA_H 1

#define PHP_KAFKA_VERSION "0.1.0-dev"
#define PHP_KAFKA_EXTNAME "kafka"
#define PHP_KAFKA_OFFSET_BEGIN "beginning"
#define PHP_KAFKA_OFFSET_END "end"
#define PHP_KAFKA_LOG_ON 1
#define PHP_KAFKA_LOG_OFF 0
#define PHP_KAFKA_MODE_CONSUMER 0
#define PHP_KAFKA_MODE_PRODUCER 1
#define PHP_KAFKA_COMPRESSION_NONE "none"
#define PHP_KAFKA_COMPRESSION_GZIP "gzip"
#define PHP_KAFKA_COMPRESSION_SNAPPY "snappy"
//option constants...
#define PHP_KAFKA_RETRY_COUNT 1
#define PHP_KAFKA_RETRY_INTERVAL 2
#define PHP_KAFKA_CONFIRM_DELIVERY 4
#define PHP_KAFKA_QUEUE_BUFFER_SIZE 8
#define PHP_KAFKA_COMPRESSION_MODE 16
#define PHP_KAFKA_LOGLEVEL 32
#define PHP_KAFKA_CONFIRM_OFF 0
#define PHP_KAFKA_CONFIRM_BASIC 1
#define PHP_KAFKA_CONFIRM_EXTENDED 2
extern zend_module_entry kafka_module_entry;

PHP_MSHUTDOWN_FUNCTION(kafka);
PHP_MINIT_FUNCTION(kafka);
PHP_RINIT_FUNCTION(kafka);
PHP_RSHUTDOWN_FUNCTION(kafka);

#ifdef ZTS
#include <TSRM.h>
#endif
#include "librdkafka/rdkafka.h"

#define PHP_KAFKA_PARTITION_RANDOM RD_KAFKA_PARTITION_UA

typedef struct _kafka_r {
    zend_object         std;
    rd_kafka_t          *consumer;
    rd_kafka_t          *producer;
    char                *brokers;
    char                *compression;
    char                *retry_count;
    char                *retry_interval;
    int                 delivery_confirm_mode;
    char                *queue_buffer;
    long                consumer_partition;
    long                producer_partition;
    int                 log_level;
    rd_kafka_type_t     rk_type;
} kafka_connection;

//attach kafka connection to module
zend_object_value create_kafka_connection(zend_class_entry *class_type TSRMLS_DC);
void free_kafka_connection(void *object TSRMLS_DC);

/* Kafka class */
static PHP_METHOD(Kafka, __construct);
static PHP_METHOD(Kafka, __destruct);
static PHP_METHOD(Kafka, setCompression);
static PHP_METHOD(Kafka, getCompression);
static PHP_METHOD(Kafka, set_partition);
static PHP_METHOD(Kafka, setPartition);
static PHP_METHOD(Kafka, getPartition);
static PHP_METHOD(Kafka, setLogLevel);
static PHP_METHOD(Kafka, getPartitionsForTopic);
static PHP_METHOD(Kafka, getPartitionOffsets);
static PHP_METHOD(Kafka, isConnected);
static PHP_METHOD(Kafka, setBrokers);
static PHP_METHOD(Kafka, setOptions);
static PHP_METHOD(Kafka, getTopics);
static PHP_METHOD(Kafka, disconnect);
static PHP_METHOD(Kafka, produceBatch);
static PHP_METHOD(Kafka, produce);
static PHP_METHOD(Kafka, consume);
PHPAPI void kafka_connect(char *brokers);

#endif
