# Research Implementation of the IETF TCP Yang Model

This repository contains the result of a research project conducted with the [Esslingen University](https://www.hs-esslingen.de/en/) in which the new IETF TCP YANG model [draft-ietf-tcpm-yang-tcp](https://datatracker.ietf.org/doc/html/draft-ietf-tcpm-yang-tcp) has been evaluated. Over the course of the project (two semesters), the internet-draft has been analyzed in detail to provide helpful feedback to the TCPM working group of the IETF about the proposed YANG model. This analysis included developing a prototype for multiple platforms (Linux and Blackberry QNX) to discover potential implementation issues and check the compatibility of the suggested YANG model with existing and commonly used operating systems.

## draft-ietf-tcpm-yang-tcp

To this date no official YANG model exists to configure and interace with the TCP stack of a device. The mentioned internet-draft, proposed by [Michael Scharf](https://datatracker.ietf.org/person/michael.scharf@hs-esslingen.de) ([Esslingen University](https://www.hs-esslingen.de/en/)), is intended to solve this problem and to provide an official standard (YANG model) for TCP on devices that are configured by network management protocols. The draft document is available at the official [Datatracker of the IETF](https://datatracker.ietf.org/doc/html/draft-ietf-tcpm-yang-tcp).

## Implementation

To implement a prototype which supports the IETF TCP Model (draft) the open-source NETCONF/YANG framework [Clixon](https://github.com/clicon/clixon) has been used. It provides a plugin architecture that can be used to easily integrate support for different YANG models into a product. The documentation for Clixon is available at [Read the Docs](https://clixon-docs.readthedocs.io/en/latest/). 

Out-of-the-box Clixon does not support the QNX operating system, so the implementation phase included porting Clixon to this new OS and ensuring everything works as expected. The changes that were required in the source code of Clixon were pushed back to the GitHub repository to make the open-source solution more powerful and extend it to further use cases.

The following implementations are available in this repository and contain their own README with additional information.

1. [tcp-plugin-ubuntu](/tcp-plugin-ubuntu)
2. tcp-plugin-qnx (coming soon)

## Contribution

The research project has been conducted by **Simon Bauer (Esslingen University)** and **Martin Mager (Esslingen University)** under the guidance of **Prof. Michael Scharf (Esslingen University)**.
